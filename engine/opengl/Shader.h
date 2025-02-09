#pragma once

#include <string>
#include <cstdint>
#include <unordered_map>

#include "glm/gtc/matrix_transform.hpp"

namespace xengine {

    struct ShaderFile
    {
        std::string vertexShader;
        std::string fragmentShader;
    };

    /*
     * This class represents a shader in OpenGL.
     * A shader is a program which runs on GPU and renders shapes on the screen.
     *
     * Currently, it manages 2 type of shaders:
     * 1) Fragment shader;
     * 2) Vertex shader;
     */

    class Shader
    {
    public:
        explicit Shader(const std::string& filePath);
        ~Shader();

        void bind() const;
        void unBind() const;

        void setUniform(const std::string& name, float red, float green, float blue, float opacity) const;
        void setTexture(const std::string& name, int slotLocation) const;
        void setUniformMat(const std::string& name, const glm::mat4& mat4) const;

        uint32_t getId() const { return m_RenderId; }

#ifdef UNIT_TESTS
        uint32_t getRendererID() const { return m_RenderId; }
        bool shaderParsedOkay() const { return parsedOkay; }
        int getUniformForTest(const std::string& name) const { return getUniformLocation(name); }
        bool gotLastUniformFromCache() const { return fromCache; }
#endif

    private:
        uint32_t m_RenderId {};
        // We want to read this from const method
        mutable std::unordered_map<std::string, int> m_UniformLocationCache;

        unsigned int compileShader(unsigned int type, const std::string& source) const;
        uint32_t createShader(const ShaderFile &shaderFile) const;
        ShaderFile parseShader(const std::string& filePath) const;

        int getUniformLocation(const std::string& name) const;

        std::string m_FilePath;

#ifdef UNIT_TESTS
        mutable bool parsedOkay = false;
        mutable bool fromCache = false;
#endif
    };

}
