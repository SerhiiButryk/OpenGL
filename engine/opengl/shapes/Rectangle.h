#pragma once

#include <array>
#include <opengl/shapes/Shape.h>

namespace xengine {

    class Rectangle 
    {
    public:
        static constexpr short VERTEX_COUNT = 4;
        using VertexData = std::array<Vertex, VERTEX_COUNT>;

        explicit Rectangle(glm::vec3 point, float width, float height);

        Vertex* getBuffer() { return m_dataBuffer.data(); }

        void setTextureIndex(float index) { m_textureIndex = index; }
        void setColor(glm::vec4 color) { m_color = color; }

        // Apply changes
        void update();

    private:
        void create();

    private:
        // Bottom left coord of the shape
        glm::vec3 m_point;

        float m_width;
        float m_height;

        // A vertex buffer which contains 4 vertices to specify the rectangle
        VertexData m_dataBuffer = {};

        // RGB Color
        glm::vec4 m_color = {0.0f, 0.0f, 0.0f, 1.0f};

        float m_textureIndex = 0.0f;
    };

}
