#pragma once

#include "RenderData.h"

namespace xengine {

    void Object::setMaterial(const glm::mat4 &modelMatrix, const std::string &shaderPath, const std::string &texturePath)
    {
        using namespace xengine;

        shader = Shader::createShader(shaderPath);
        shader->bind();

        if (!texturePath.empty()) {

            // TODO: Loading a shape makes program very slow off load this to background thread
            texture = Texture::createTexture(texturePath);

            shader->setTextureUniform("u_Texture", 0);
        }

        glm::mat4 projMatrix = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

        glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

        shader->setUniformMat("u_Model", modelMatrix);
        shader->setUniformMat("u_View", viewMatrix);
        shader->setUniformMat("u_Projection", projMatrix);

        shader->unBind();
    }

}