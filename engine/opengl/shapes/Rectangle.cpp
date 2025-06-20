#include "Rectangle.h"

namespace xengine {

    Rectangle::Rectangle(float width, float height) : m_width(width), m_height(height) {
        Rectangle::updateBuffer();
    }

    void Rectangle::updateBuffer() {

        // Default texture coordinates
        glm::vec2 t1 = {0.0f, 0.0f};
        glm::vec2 t2 = {1.0f, 0.0f};
        glm::vec2 t3 = {1.0f, 1.0f};
        glm::vec2 t4 = {0.0f, 1.0f};

        glm::vec2 textureCoords[] = {t1, t2, t3, t4};

        glm::vec3 center = {0.0f, 0.0f, 0.0f};

        glm::vec3 coord1 = {center.x - m_width / 2, center.y - m_height / 2, 0.0f};
        glm::vec3 coord2 = {center.x + m_width / 2, center.y - m_height / 2, 0.0f};
        glm::vec3 coord3 = {center.x + m_width / 2, center.y + m_height / 2, 0.0f};
        glm::vec3 coord4 = {center.x - m_width / 2, center.y + m_height / 2, 0.0f};

        glm::vec3 coords[] = { coord1, coord2, coord3, coord4};

        for (int i = 0; i < getVertexCount(); ++i) {
            m_dataBuffer[i] = { coords[i], m_color, textureCoords[i], m_textureIndex };
        }

    }

    void Rectangle::setIndicies(uint32_t* indices, uint32_t maxSize) {

        uint32_t offset = 0;

        // '6' represents 2 triangles with 3 * 2 vertices
        for (int i = 0; i < maxSize; i += 6 /* Makes up a single quad */) {

            indices[i + 0] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;

            indices[i + 3] = 2 + offset;
            indices[i + 4] = 3 + offset;
            indices[i + 5] = 0 + offset;

            offset += 4;
        }

    }
}
