#pragma once

#include <opengl/shapes/Rectangle.h>
#include <opengl/shapes/Triangle.h>

namespace test {

    class ComponentUIFactory 
    {
    public:

        static xengine::Rectangle* createRectShape(glm::vec3 point, glm::vec4 color, float texutureIndex = -1.0f);

        static xengine::Triangle* createTriangleShape(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec4 color);
    };

}
