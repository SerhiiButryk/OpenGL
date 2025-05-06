#pragma once

#include <array>
#include <opengl/shapes/Shape.h>

namespace xengine {

    class Rectangle : public Shape
    {
    public:
        static constexpr short VERTEX_COUNT = 4;
        using VertexData = std::array<Vertex, VERTEX_COUNT>;

        explicit Rectangle(glm::vec3 point, float width, float height);

        Vertex* getBuffer() override { return m_dataBuffer.data(); }

        void setTextureIndex(float index) { m_textureIndex = index; }

        void create() override;

        uint32_t getVertexCount() const override { return VERTEX_COUNT; }

        glm::vec3 getCoord() const {
            return m_point;
        }

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
        // Center coord of the shape
        glm::vec3 m_point;

        float m_width = 0.0f;
        float m_height = 0.0f;

        // A vertex buffer which contains 4 vertices to specify the rectangle
        VertexData m_dataBuffer = {};

        // No texture by default
        float m_textureIndex = -1.0f;
    };

}
