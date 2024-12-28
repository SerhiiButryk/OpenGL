#pragma once

#include <array>
#include <opengl/shapes/Shape.h>

namespace xengine {

    class Rectangle 
    {
    public:
        static constexpr short SIZE = 4;
        using VertexData = std::array<Vertex, SIZE>;

        explicit Rectangle(Point point, float width, float height);

        const VertexData& getBuffer() { return m_dataBuffer; }

        void setTextureIndex(float index) { m_textureIndex = index; }
        void setColor(Color color) { m_color = color; }

        // Apply changes
        void update();

    private:
        void create();

    private:
        // Bottom left coord of the shape
        Point m_point;

        float m_width;
        float m_height;

        // A vertex buffer which contains 4 vertices to specify the rectangle
        VertexData m_dataBuffer = {};

        // RGB Color
        Color m_color = {0.0f, 0.0f, 0.0f, 1.0f};

        float m_textureIndex = 0.0f;
    };

}
