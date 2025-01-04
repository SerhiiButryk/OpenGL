#pragma once

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <opengl/Layout.h>

namespace xengine {

    #define VERTEX_ELEMENT_COUNT(x) sizeof (decltype(x)) / sizeof (decltype(x)::value_type)
    // Size in bytes for N vertices
    #define VERTEX_TOTAL_SIZE(VERTEX_COUNT) (sizeof(Vertex) * VERTEX_COUNT)

    // Update the layout if you add/modify this vertex
    struct Vertex {

        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 texCoord;
        float texIndex;

        static BufferLayout getLayout() {
            BufferLayout layout;
            // Order is very important here. Should reflect the vertex data structure
            layout.add({VERTEX_ELEMENT_COUNT(position), GL_FLOAT, GL_FALSE });
            layout.add({VERTEX_ELEMENT_COUNT(color), GL_FLOAT, GL_FALSE });
            layout.add({VERTEX_ELEMENT_COUNT(texCoord), GL_FLOAT, GL_FALSE });
            layout.add({1, GL_FLOAT, GL_FALSE });
            return layout;
        }
    };

}
