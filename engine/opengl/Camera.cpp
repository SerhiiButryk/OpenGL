#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace xengine {

    Camera::Camera(float left, float right, float bottom, float top) {
        recalculate();
    }

    // TODO: Revisit camera

    // void Camera::recalculate() {
    //
    //     glm::mat4 identityMat = glm::mat4(1.0f);
    //     glm::vec3 transVec = m_Position;
    //
    //     // Create translation matrix
    //     glm::mat4 transMat = glm::translate(identityMat, transVec);
    //
    //     // Create rotation matrix
    //     // We specify rotation around Z-axis
    //     auto zAxis = glm::vec3(0, 0, 1);
    //     glm::mat4 rotateMat = glm::rotate(identityMat, glm::radians(m_Rotation), zAxis);
    //
    //     // Note: Remember that the actual transformation order should be read in reverse:
    //     // though in code we first translate and then later rotate, the actual transformations first apply
    //     // a rotation and then a translation.
    //     transMat = transMat * rotateMat;
    //
    //     // To move a camera backwards, is the same as moving the entire scene forward.
    //     // That is exactly what a view matrix does, we move the entire scene around inversed to where we want the camera to move.
    //     m_ViewMatrix = glm::inverse(transMat);
    //
    //     // Resulting projection matrix
    //     m_ViewProjMatrix = m_ProjectionMatrix * m_ViewMatrix;
    // }

    void Camera::recalculate() {

        glm::mat4 model = glm::mat4(1.0f);
        m_ModelMatrix = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 view = glm::mat4(1.0f);
        // note that we're translating the scene in the reverse direction of where we want to move
        m_ViewMatrix = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        // glm::mat4 projection;
        m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

        // Resulting projection matrix
        // m_ViewProjMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

}
