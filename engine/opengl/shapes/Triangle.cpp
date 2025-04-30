#include "Triangle.h"

namespace xengine {

    Triangle::Triangle() {
    }

    void Triangle::create() {

    }

    void Triangle::addVertex(glm::vec3 position) {

        Vertex vertex = { position, m_color, {0.0f, 0.0f}, m_textureIndex };

        m_dataBuffer[m_dataBufferIndex++] = vertex;
    }

}
