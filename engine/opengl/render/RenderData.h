#pragma once

#include <opengl/Camera.h>
#include <opengl/IndexBuffer.h>
#include <opengl/Shader.h>
#include <opengl/Textures.h>
#include <opengl/VertexArray.h>
#include <opengl/shapes/Rectangle.h>

namespace xengine {

    /**
     * A data for our render
     */
    class RenderData
    {
    public:

        static constexpr unsigned int DEFAULT_VERTEX_BUFF_SIZE = 100;
        static constexpr unsigned int DEFAULT_INDEX_BUFF_SIZE = 100;

        // Some context configs/data
        struct RendererConfigs {

            int width {}, height {}; // window size information in pixels
            std::string assetsPath;

            uint32_t vertexCount {}; // number of vertices
            uint32_t indexBufferMaxSize {};

            void* drawBuffer = nullptr; // actual data buffer
            void* nextElementPointer = nullptr; // pointer to the next vertex place in the buffer

            // Controlled by Camera class
            glm::mat4 viewProjMatrix = glm::mat4(1.0f);
        };

        // Per object configs/data
        struct Objects {

            Shape* shape = nullptr;

            Shader* shader = nullptr;
            VertexArray* vertexArray = nullptr;
            VertexBuffer* vertexBuffer = nullptr;
            IndexBuffer* indexBuffer = nullptr;
            Texture* texture = nullptr;

            glm::mat4 tansform = glm::mat4(1.0f);
        };

        RendererConfigs configs = {};

        /**
         * Releases all resources and states for the current Render data object
         */
        void clear();

    };

}
