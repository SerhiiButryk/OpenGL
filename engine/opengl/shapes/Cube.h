#pragma once

#include "Shape.h"
#include <array>

namespace xengine {

    class Cube : public Shape
    {
        public:
            Cube();
            ~Cube() override = default;

            Vertex* getBuffer() override { return m_dataBuffer.data(); }

            uint32_t getVertexCount() const override { return VERTEX_COUNT; }
            uint32_t getElementCount() const override { return 36; }

            void updateBuffer() override;

            void setIndicies(uint32_t *indices, uint32_t maxSize) override;

        private:
            static constexpr short VERTEX_COUNT = 8;
            using VertexData = std::array<Vertex, VERTEX_COUNT>;

            VertexData m_dataBuffer = {};

    };

}
