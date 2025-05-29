#include "ComponentUIFactory.h"

namespace test {

    xengine::Rectangle *ComponentUIFactory::createRectShape(glm::vec3 centerPoint, glm::vec4 color,
                                                                       float texutureIndex, float width,
                                                                       float height) {

        using namespace xengine;

        auto shape = new Rectangle(centerPoint, width, height);

        shape->setColor(color);
        shape->setTextureIndex(texutureIndex);

        shape->create();

        return shape;
    }

    xengine::Triangle* ComponentUIFactory::createTriangleShape(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec4 color) {

        using namespace xengine;

        auto shape = new Triangle();

        shape->setColor(color);

        shape->setPoint(point1, 0);
        shape->setPoint(point2, 1);
        shape->setPoint(point3, 2);

        return shape;
    }

}
