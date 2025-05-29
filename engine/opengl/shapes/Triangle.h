#pragma once

#include <array>
#include <opengl/shapes/Shape.h>

namespace xengine {

    class Triangle : public Shape
    {
    public:
        static constexpr short VERTEX_COUNT = 3;
        using VertexData = std::array<Vertex, VERTEX_COUNT>;

        Triangle();

        void setTextureIndex(float index) { m_textureIndex = index; }

        uint32_t getVertexCount() const override { return VERTEX_COUNT; }

        Vertex* getBuffer() override { return m_dataBuffer.data(); }

        void setPoint(glm::vec3 point, int index);

    private:
        // No texture by default
        float m_textureIndex = -1.0f;

        VertexData m_dataBuffer = {};
    };

}