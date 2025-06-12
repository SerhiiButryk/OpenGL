#pragma once

#include <glm/glm.hpp>

namespace xengine {

    // Local space (or Object space)
    // World space
    // View space (or Eye space)
    // Clip space
    // Screen space

    // 1. Local coordinates are the coordinates of your object relative to its local origin; they're the coordinates your object begins in.

    // 2. The next step is to transform the local coordinates to world-space coordinates which are coordinates in respect
    // of a larger world. These coordinates are relative to some global origin of the world, together with many other
    // objects also placed relative to this world's origin.

    // 3. Next we transform the world coordinates to view-space coordinates in such a way that each coordinate
    // is as seen from the camera or viewer's point of view.

    // 4. After the coordinates are in view space we want to project them to clip coordinates.
    // Clip coordinates are processed to the -1.0 and 1.0 range and determine which vertices will end up on the screen.
    // Projection to clip-space coordinates can add perspective if using perspective projection.

    // 5. And lastly we transform the clip coordinates to screen coordinates in a process we call viewport
    // transform that transforms the coordinates from -1.0 and 1.0 to the coordinate range defined by glViewport.
    // The resulting coordinates are then sent to the rasterizer to turn them into fragments.

    // Model space to View space - View matrix
    // View space to Clip space - Projection matrix

    class Camera {

    public:
        Camera(float left, float right, float bottom, float top);

        const glm::vec3& getPosition() const {
            return m_Position;
        }

        void setPosition(const glm::vec3 &position) {
            m_Position = position;
            recalculate();
        }

        float getRotation() const {
            return m_Rotation;
        }

        void setRotation(float rotation) {
            m_Rotation = rotation;
            recalculate();
        }

        const glm::mat4& getProjectionMatrix() const {
            return m_ProjectionMatrix;
        }

        const glm::mat4& getViewMatrix() const {
            return m_ViewMatrix;
        }

        const glm::mat4& getModelMatrix() const {
            return m_ModelMatrix;
        }

    private:
        void recalculate();

    private:
        glm::mat4 m_ProjectionMatrix = {1.0f};
        glm::mat4 m_ViewMatrix = {1.0f};
        glm::mat4 m_ModelMatrix = {1.0f};

        glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
        float m_Rotation = 0.0f;
    };
}
