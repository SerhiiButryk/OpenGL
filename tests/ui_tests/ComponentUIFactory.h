#pragma once

#include <opengl/render/RenderDirector.h>
#include <opengl/shapes/Shape.h>
#include <opengl/shapes/Triangle.h>

namespace test {

    class ComponentUIFactory 
    {
    public:
        static void submitShape(xengine::Shape* shape, xengine::RenderDirector* director,
            xengine::RenderData* data, const char* shaderName);

        static xengine::Rectangle* createRectShape(glm::vec3 point, glm::vec4 color);

        static xengine::Triangle* createTriangleShape(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec4 color);
    };

}
