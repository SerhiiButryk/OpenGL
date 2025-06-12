#pragma once

#include <array>
#include <opengl/shapes/Shape.h>

namespace xengine {

    class Rectangle : public Shape
    {
    public:
        static constexpr short VERTEX_COUNT = 4;
        using VertexData = std::array<Vertex, VERTEX_COUNT>;

        explicit Rectangle(float width, float height);

        Vertex* getBuffer() override { return m_dataBuffer.data(); }

        void create() override;

        uint32_t getVertexCount() const override { return VERTEX_COUNT; }
        uint32_t getElementCount() const override { return 6; }

        float getWidth() const {
            return m_width;
        }

        float getHeight() const {
            return m_height;
        }

        float getTextureIndex() const {
            return m_textureIndex;
        }

    private:

        float m_width = 0.0f;
        float m_height = 0.0f;

        // A vertex buffer which contains 4 vertices to specify the rectangle
        VertexData m_dataBuffer = {};
    };

}
