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

        void create() override;

        void addVertex(glm::vec3 position);

    private:
        // No texture by default
        float m_textureIndex = -1.0f;

        VertexData m_dataBuffer = {};
        unsigned int m_dataBufferIndex = 0;
    };

}