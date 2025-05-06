#include "ComponentUIFactory.h"

namespace test {

    void ComponentUIFactory::submitShape(xengine::Shape *shape,
        xengine::RenderGL* renderer, xengine::RenderData* data, const char* shaderName) {

        renderer->begin(data);

        renderer->setShader(shaderName);
        // TODO: Configure
        renderer->setTexture("test.png", "u_Texture");

        renderer->submit(shape);

        renderer->end();
    }

    xengine::Rectangle* ComponentUIFactory::createRectShape(glm::vec3 point, glm::vec4 color, float texutureIndex) {

        using namespace xengine;

        float defaultWidth = 1.0f;
        float defaultHeight = 1.0f;

        auto shape = new Rectangle(point, defaultWidth, defaultHeight);

        shape->setColor(color);
        shape->setTextureIndex(texutureIndex);

        shape->applyNewValues();

        return shape;
    }

    xengine::Triangle* ComponentUIFactory::createTriangleShape(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec4 color) {

        using namespace xengine;

        auto shape = new Triangle();

        shape->setColor(color);

        shape->addVertex(point1);
        shape->addVertex(point2);
        shape->addVertex(point3);

        return shape;
    }

}
