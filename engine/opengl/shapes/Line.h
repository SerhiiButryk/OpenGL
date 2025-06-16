#pragma once

#include <array>
#include <glm/vec3.hpp>

#include "Shape.h"

namespace xengine {

    class Line : public Shape
    {
    public:
        static constexpr short VERTEX_COUNT = 2;
        using VertexData = std::array<Vertex, VERTEX_COUNT>;

        explicit Line(glm::vec3 pointStart, glm::vec3 pointEnd, short thickness = 0);

        Vertex* getBuffer() override { return m_dataBuffer.data(); }

        uint32_t getVertexCount() const override { return VERTEX_COUNT; }

        void updateBuffer() override;

    private:
        glm::vec3 m_pointStart;
        glm::vec3 m_pointEnd;

        float m_thickness = {};

        VertexData m_dataBuffer = {};
    };

}