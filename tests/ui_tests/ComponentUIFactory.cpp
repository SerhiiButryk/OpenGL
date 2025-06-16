#include "ComponentUIFactory.h"

#include <opengl/shapes/Rectangle.h>
#include <opengl/shapes/Triangle.h>

namespace test {

    void setMaterial(xengine::Object* object, const glm::mat4& modelMatrix, const std::string& shaderPath,
        const std::string& texturePath, float textureIndex) {

        using namespace xengine;

        object->shader = Shader::createShader(shaderPath);
        object->shader->bind();

        if (textureIndex > 0) {

            // TODO: Loading a shape makes program very slow off load this to background thread
            object->texture = Texture::createTexture(texturePath);

            object->shader->setTextureUniform("u_Texture", 0);
        }

        glm::mat4 projMatrix = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

        glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

        object->shader->setUniformMat("u_Model", modelMatrix);
        object->shader->setUniformMat("u_View", viewMatrix);
        object->shader->setUniformMat("u_Projection", projMatrix);
    }

    xengine::Object* ComponentUIFactory::createRectShape(const std::string& shaderPath, const std::string& texturePath,
        const glm::mat4& modelMatrix, glm::vec4 color, float width, float height, float textureIndex)
    {
        using namespace xengine;

        auto object = new Object();

        auto shape = new Rectangle(width, height);

        shape->setColor(color);
        shape->setTextureIndex(textureIndex);

        object->shape = shape;

        setMaterial(object, modelMatrix, shaderPath, texturePath, textureIndex);

        return object;
    }

    xengine::Object* ComponentUIFactory::createTriangleShape(const std::string& shaderPath, const std::string& texturePath,
        const glm::mat4& modelMatrix, glm::vec4 color, glm::vec3 points[], float textureIndex)
    {
        using namespace xengine;

        auto object = new Object();

        auto shape = new Triangle();

        shape->setColor(color);

        shape->setPoint(points[0], 0);
        shape->setPoint(points[1], 1);
        shape->setPoint(points[2], 2);

        object->shape = shape;

        setMaterial(object, modelMatrix, shaderPath, texturePath, textureIndex);

        return object;
    }
}
