#include "Rectangle.h"

namespace xengine {

    Rectangle::Rectangle(float width, float height) : m_width(width), m_height(height) {
        Rectangle::updateBuffer();
    }

    void Rectangle::updateBuffer() {

        // Default texture coordinates
        glm::vec2 c1 = {0.0f, 0.0f};
        glm::vec2 c2 = {1.0f, 0.0f};
        glm::vec2 c3 = {1.0f, 1.0f};
        glm::vec2 c4 = {0.0f, 1.0f};

        glm::vec3 center = {0.0f, 0.0f, 0.0f};

        // Bottom left point
        m_dataBuffer[0] = { { center.x - m_width / 2, center.y - m_height / 2, 0.0f },
            m_color,
            c1,
            m_textureIndex };

        // Bottom right point
        m_dataBuffer[1] = { { center.x + m_width / 2, center.y - m_height / 2, 0.0f },
            m_color,
            c2,
            m_textureIndex };

        // Top right point
        m_dataBuffer[2] = { { center.x + m_width / 2, center.y + m_height / 2, 0.0f },
            m_color,
            c3,
            m_textureIndex};

        // Top left point
        m_dataBuffer[3] = { { center.x - m_width / 2, center.y + m_height / 2, 0.0f },
            m_color,
            c4,
            m_textureIndex};
    }
}
