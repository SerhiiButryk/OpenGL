#pragma once

#include <string>
#include <cstdint>

#include "glm/gtc/matrix_transform.hpp"

namespace xengine {

struct ShaderFile
{
    std::string vertexShader;
    std::string fragmentShader;
};

/*
 * This class represents a shader in our program.
 * A shader is a program which runs on GPU and renders shapes on the screen.
 *
 * Currently, it manages 2 type of shaders:
 * 1) Fragment shader;
 * 2) Vertex shader;
 */

class Shader
{
public:
    Shader(const std::string& filePath);
    ~Shader();

    void bind() const;
    void unBind() const;

    void setUniform(const std::string& name, float red, float green, float blue, float opacity) const;
    void setUniformTexture(const std::string& name, int slotLocation) const;
    void setUniformMat(const std::string& name, const glm::mat4& mat4) const;

private:
    uint32_t m_RenderId {};

    unsigned int compileShader(unsigned int type, const std::string& source) const;
    uint32_t createShader(ShaderFile shaderFile) const;
    ShaderFile parseShader(const std::string& filePath) const;

    int getUniformLocation(const std::string& name) const;
};

}
