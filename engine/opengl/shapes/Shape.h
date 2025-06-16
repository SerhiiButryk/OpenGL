#pragma once

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <opengl/Layout.h>

#include "Color.h"

namespace xengine {

    #define VERTEX_ELEMENT_COUNT(x) sizeof (decltype(x)) / sizeof (decltype(x)::value_type)
    // Size in bytes for N vertices
    #define VERTEX_TOTAL_SIZE(VERTEX_COUNT) (sizeof(Vertex) * VERTEX_COUNT)

    // TODO: For different shapes we might need to create different vertices like VertexLine VertexCircle but don't do that for simplicity
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

    class UniqueIDGenerator {
    public:
        static unsigned int getNextID() {
            static unsigned int counter = 0;
            return ++counter;
        }
    };

    class Shape {

        public:

            Shape() = default;
            virtual ~Shape() = default;

            virtual Vertex* getBuffer() = 0;

            virtual uint32_t getVertexCount() const = 0;
            virtual uint32_t getElementCount() const { return 0; }

            unsigned int getID() const { return m_ID; }

            void setColor(glm::vec4 color) { m_color = color; updateBuffer(); }
            glm::vec4 getColor() const { return m_color; }

            void setTextureIndex(float index) { m_textureIndex = index; updateBuffer(); }

            float getTextureIndex() const {
                return m_textureIndex;
            }

            virtual void updateBuffer() {}

            void invalidate() { invalid = true; }
            void reset() { invalid = false; }
            bool isInvalid() const { return invalid; }

        protected:
            // RGB Color
            glm::vec4 m_color = Color(BLACK_COLOR);
            // ID
            unsigned int m_ID = UniqueIDGenerator::getNextID();
            // No texture by default
            float m_textureIndex = -1.0f;
            // Marks if shape has changed and it should drown again
            bool invalid = false;
    };

}
