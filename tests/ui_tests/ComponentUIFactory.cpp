#include "ComponentUIFactory.h"

#include <opengl/shapes/Cube.h>
#include <opengl/shapes/Rectangle.h>
#include <opengl/shapes/Triangle.h>

namespace test {

    xengine::Object* ComponentUIFactory::createRectShape(const std::string& shaderPath, const std::string& texturePath,
        const glm::mat4& modelMatrix, glm::vec4 color, float width, float height, float textureIndex)
    {
        using namespace xengine;

        auto object = new Object();

        auto shape = new Rectangle(width, height);

        shape->setColor(color);
        shape->setTextureIndex(textureIndex);

        object->shape = shape;

        object->setMaterial(modelMatrix, shaderPath, texturePath);

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

        object->setMaterial(modelMatrix, shaderPath, texturePath);

        return object;
    }

    xengine::Object* ComponentUIFactory::createCubeShape(const std::string& shaderPath, const std::string& texturePath, const glm::mat4& modelMatrix)
    {
        using namespace xengine;

        auto object = new Object();

        auto shape = new Cube();

        object->shape = shape;

        object->setMaterial(modelMatrix, shaderPath, texturePath);

        return object;
    }
}
