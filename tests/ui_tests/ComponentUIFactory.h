#pragma once

#include <opengl/render/RenderData.h>

namespace test {

    class ComponentUIFactory {
    public:

        static xengine::Object* createRectShape(const std::string& shaderPath, const std::string& texturePath,
            const glm::mat4& modelMatrix = glm::mat4(1.0f), glm::vec4 color = {},
            float width = 1.0f, float height = 1.0f, float textureIndex = -1.0f);

        static xengine::Object* createTriangleShape(const std::string& shaderPath, const std::string& texturePath,
            const glm::mat4& modelMatrix, glm::vec4 color, glm::vec3 points[], float textureIndex = -1.0f);

        static xengine::Object* createCubeShape(const std::string& shaderPath, const std::string& texturePath,
            const glm::mat4& modelMatrix);
    };
}
