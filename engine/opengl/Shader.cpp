#include "Shader.h"

#include <common/Log.h>

#include <filesystem>
#include <fstream>

/* Glew is included first because it loads and provides OpenGL APIs to use later */
#include <GL/glew.h>

Shader::Shader(const std::string& filePath)
{
    auto shaderFile = parseShader(filePath);
    m_RenderId = createShader(shaderFile);
    logInfo("Shader::Shader() created, id = {}", m_RenderId);
}

Shader::~Shader()
{
    glDeleteProgram(m_RenderId);
    logInfo("Shader::~Shader() Destroyed");
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
    int location = glGetUniformLocation(m_RenderId, name.c_str()); // Get the id of uniform variable
    if (location == -1) {
        // This can mean that uniform is not active
        logError("Shader::setUniform() unable to get uniform location for {}", name);
    }
    return location;
}

void Shader::setUniform(const std::string& name, float red, float green, float blue, float opacity) const
{
    int location = getUniformLocation(name);
    glUniform4f(location, red, green, blue, opacity); // Set a color in RGB format
}

void Shader::setUniformTexture(const std::string& name, int slotLocation) const {
    int location = getUniformLocation(name);
    glUniform1i(location, slotLocation);
}

void Shader::setUniformMat(const std::string& name, const glm::mat4& mat4) const {
    int location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, &mat4[0][0]);
}

ShaderFile Shader::parseShader(const std::string& filePath) const
{
    std::filesystem::path current_path = std::filesystem::current_path();
    logInfo("Shader::parseShader() My working dir: '{}'", current_path.string());

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

    if (shaderFile.vertexShader.empty()) {
        logError("Vertex shader is empty !");
    } else {
        logInfo("Vertex shader: \n \"{}\"", shaderFile.vertexShader);
    }

    if (shaderFile.fragmentShader.empty()) {
        logError("Fragment shader is empty !");
    } else {
        logInfo("Fragment shader: \n \"{}\"", shaderFile.fragmentShader);
    }

    return shaderFile;
}

uint32_t Shader::createShader(ShaderFile shaderFile) const
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, shaderFile.vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, shaderFile.fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

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

        logError("Failed to compile: {}", message);

        glDeleteShader(id);

        return 0;
    }

    return id;
}
