#pragma once

#include "Shape.h"
#include <array>

namespace xengine {

    class Cube : public Shape
    {
        public:
            // A total of 36 vertices (6 faces * 2 triangles * 3 vertices each)
            static constexpr short VERTEX_COUNT = 36;
            using VertexData = std::array<Vertex, VERTEX_COUNT>;

            Cube();
            ~Cube() override = default;

            Vertex* getBuffer() override { return m_dataBuffer.data(); }

            void updateBuffer() override;

        private:

            // A vertex buffer which contains 4 vertices to specify the rectangle
            VertexData m_dataBuffer = {};

    };

}
