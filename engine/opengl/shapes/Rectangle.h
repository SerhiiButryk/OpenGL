#pragma once

#include <array>
#include <opengl/shapes/Shape.h>

namespace xengine {

    class Rectangle : public Shape
    {
    public:
        explicit Rectangle(float width, float height);

        Vertex* getBuffer() override { return m_dataBuffer.data(); }

        void updateBuffer() override;

        uint32_t getVertexCount() const override { return VERTEX_COUNT; }
        uint32_t getElementCount() const override { return 6; }

        float getWidth() const {
            return m_width;
        }

        float getHeight() const {
            return m_height;
        }

        void setIndicies(uint32_t* indices, uint32_t maxSize) override;

    private:
        static constexpr short VERTEX_COUNT = 4;
        using VertexData = std::array<Vertex, VERTEX_COUNT>;

        float m_width = 0.0f;
        float m_height = 0.0f;

        // A vertex buffer which contains 4 vertices to specify the rectangle
        VertexData m_dataBuffer = {};
        uint32_t indexBuffer[VERTEX_COUNT] = {};
    };

}
