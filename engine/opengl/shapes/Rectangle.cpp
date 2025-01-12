#include "Rectangle.h"

namespace xengine {

    Rectangle::Rectangle(glm::vec3 point, float width, float height)
        : m_point(point), m_width(width), m_height(height) {

        Rectangle::create();
    }

    void Rectangle::create() {

        // Default texture coordinates
        glm::vec2 c1 = {0.0f, 0.0f};
        glm::vec2 c2 = {1.0f, 0.0f};
        glm::vec2 c3 = {1.0f, 1.0f};
        glm::vec2 c4 = {0.0f, 1.0f};

        // Bottom left point
        m_dataBuffer[0] = { { m_point.x - m_width * 0.5f, m_point.y - m_height * 0.5f, m_point.z },
            m_color,
            c1,
            m_textureIndex };

        // Bottom right point
        m_dataBuffer[1] = { { m_point.x + m_width * 0.5f, m_point.y - m_height * 0.5f, m_point.z },
            m_color,
            c2,
            m_textureIndex };

        // Top right point
        m_dataBuffer[2] = { { m_point.x + m_width * 0.5f, m_point.y + m_height * 0.5f, m_point.z },
            m_color,
            c3,
            m_textureIndex};

        // Top left point
        m_dataBuffer[3] = { { m_point.x - m_width * 0.5f, m_point.y + m_height * 0.5f, m_point.z },
            m_color,
            c4,
            m_textureIndex};
    }
}
