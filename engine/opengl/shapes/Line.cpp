#include "Line.h"

#include "Rectangle.h"

namespace xengine {

    Line::Line(glm::vec3 pointStart, glm::vec3 pointEnd, short thickness)
        : m_pointStart(pointStart), m_pointEnd(pointEnd), m_thickness(thickness) {

        Line::updateBuffer();
    }

    void Line::updateBuffer() {

        m_dataBuffer[0] = {
            m_pointStart, m_color, {0.0f, 0.0f}, -1.0f
        };

        m_dataBuffer[1] = {
            m_pointEnd, m_color, {0.0f, 0.0f}, -1.0f
        };

    }

}
