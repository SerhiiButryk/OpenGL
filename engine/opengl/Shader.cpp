#include "Shader.h"

#include <common/Log.h>

#include <filesystem>
#include <fstream>

/* Glew is included first because it loads and provides OpenGL APIs to use later */
#include <GL/glew.h>

namespace xengine {

    Shader::Shader(const std::string& filePath)
    {
        m_FilePath = filePath;
        auto shaderFile = parseShader(filePath);
        m_RenderId = createShader(shaderFile);
        LOG_INFO("Shader::Shader() created, id = {}", m_RenderId);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_RenderId);
        LOG_INFO("Shader::~Shader() Destroyed");
    }

    void Shader::bind() const
    {
        glUseProgram(m_RenderId);
    }

    void Shader::unBind() const
    {
        glUseProgram(0);
    }

    int Shader::getUniformLocation(const std::string& name) const {

#ifdef UNIT_TESTS
        fromCache = false;
#endif

        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
            int location = m_UniformLocationCache[name];
            LOG_DEBUG("Shader::setUniform() from the cache '{}:{}'", name, location);
#ifdef UNIT_TESTS
            fromCache = true;
#endif
            return location;
        }

        LOG_DEBUG("Shader::setUniform() variable '{}' is not in the cache", name);

        int location = glGetUniformLocation(m_RenderId, name.c_str()); // Get the id of uniform variable
        if (location == -1) {
            // This can mean that uniform is not active or not found
            LOG_WARN("Shader::setUniform() unable to get uniform location for {}", name);
        }

        // Cache the location
        m_UniformLocationCache[name] = location;

        LOG_DEBUG("Shader::setUniform() location = {}", location);
        return location;
    }

    void Shader::setUniform(const std::string& name, float red, float green, float blue, float opacity) const
    {
        int location = getUniformLocation(name);
        if (location != -1) {
            glUniform4f(location, red, green, blue, opacity); // Set a color in RGB format
        }
    }

    void Shader::setTextureUniform(const std::string& name, int slotLocation) const {
        int location = getUniformLocation(name);
        if (location != -1) {
            glUniform1i(location, slotLocation);
        }
    }

    void Shader::setUniformMat(const std::string& name, const glm::mat4& mat4) const {
        int location = getUniformLocation(name);
        if (location != -1) {
            glUniformMatrix4fv(location, 1, GL_FALSE, &mat4[0][0]);
        }
    }

    ShaderFile Shader::parseShader(const std::string& filePath) const
    {
        std::filesystem::path current_path = std::filesystem::current_path();
        LOG_INFO("Shader::parseShader() Working dir: '{}', file path: '{}'", current_path.string(), filePath);

        std::ifstream istream(filePath);

        std::string line;
        std::stringstream vertexShaderStream;
        std::stringstream fragmentShaderStream;

        std::stringstream* current = nullptr;

        auto VERTEX_SHADER_TAG = "#vertex_shader";
        auto FRAGMENT_SHADER_TAG = "#fragment_shader";

        while (std::getline(istream, line))
        {
            if (line.find(VERTEX_SHADER_TAG) != std::string::npos)
            {
                current = &vertexShaderStream;
            }
            else if (line.find(FRAGMENT_SHADER_TAG) != std::string::npos)
            {
                current = &fragmentShaderStream;
            }
            else
            {
                current->write(line.c_str(), line.size());
                current->put('\n');
            }
        }

        ShaderFile shaderFile { vertexShaderStream.str(), fragmentShaderStream.str() };

#ifdef UNIT_TESTS
        parsedOkay = true;
#endif

        if (shaderFile.vertexShader.empty()) {
            LOG_ERROR("Vertex shader is empty !");
#ifdef UNIT_TESTS
            parsedOkay = false;
#endif
        } else {
            LOG_DEBUG("Vertex shader: \n \"{}\"", shaderFile.vertexShader);
        }

        if (shaderFile.fragmentShader.empty()) {
            LOG_ERROR("Fragment shader is empty !");
#ifdef UNIT_TESTS
            parsedOkay = false;
#endif
        } else {
            LOG_DEBUG("Fragment shader: \n \"{}\"", shaderFile.fragmentShader);
        }

        return shaderFile;
    }

    bool checkErrors(unsigned int id, int status) {
        int result;
        glGetProgramiv(id, status, &result);

        if (result == GL_FALSE)
        {
            int length;
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

            char* message = (char*)alloca(length * sizeof(char));

            glGetProgramInfoLog(id, length, &length, message);

            if (status == GL_LINK_STATUS)
                LOG_ERROR("Failed to link: {}", message);
            else if (status == GL_VALIDATE_STATUS)
                LOG_ERROR("Failed to validate: {}", message);

            return false;
        }

        return true;
    }

    uint32_t Shader::createShader(const ShaderFile &shaderFile) const
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = compileShader(GL_VERTEX_SHADER, shaderFile.vertexShader);
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, shaderFile.fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);

        if (!checkErrors(program, GL_LINK_STATUS)) {
            glDeleteShader(vs);
            glDeleteShader(fs);
            return 0;
        }

        glValidateProgram(program);

        if (!checkErrors(program, GL_VALIDATE_STATUS)) {
            glDeleteShader(vs);
            glDeleteShader(fs);
            return 0;
        }

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    unsigned int Shader::compileShader(unsigned int type, const std::string& source) const
    {
        unsigned int id = glCreateShader(type);

        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        // Error handling

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

            char* message = (char*)alloca(length * sizeof(char));

            glGetShaderInfoLog(id, length, &length, message);

            LOG_ERROR("Failed to compile: {}", message);

            glDeleteShader(id);

            return 0;
        }

        return id;
    }

}
