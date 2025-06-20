#include "Triangle.h"

#include <stdexcept>

namespace xengine {

    Triangle::Triangle() {
    }

    void Triangle::setPoint(glm::vec3 point, int index) {

        if (index < 0 || index >= 3) {
            throw std::invalid_argument("index out of range");
        }

        glm::vec2 textCoord = {0.0f, 0.0f};

        Vertex vertex = { point, m_color, textCoord, m_textureIndex };

        m_dataBuffer[index] = vertex;
    }

    void Triangle::setIndicies(uint32_t *indices, uint32_t maxSize) {
        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;
    }
}
