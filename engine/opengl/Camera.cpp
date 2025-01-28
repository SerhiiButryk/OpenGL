#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace xengine {

    Camera::Camera(float left, float right, float bottom, float top)
        : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f) {
        m_ViewProjMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void Camera::recalculate() {

        // Apply rotation and position
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}
