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

        struct Configs {

            int width {}, height {}; // window size information in pixels
            std::string assetsPath;

            uint32_t vertexCount {}; // number of vertices
            uint32_t indexBufferMaxSize {};

            void* drawBuffer = nullptr; // actual data buffer
            void* nextElementPointer = nullptr; // pointer to the next vertex place in the buffer
        };

        Shader* shader = nullptr;
        VertexArray* vertexArray = nullptr;
        VertexBuffer* vertexBuffer = nullptr;
        IndexBuffer* indexBuffer = nullptr;
        Texture* texture = nullptr;

        // Camera is not owned by this class
        Camera* camera = nullptr;

        glm::mat4 tansform = glm::mat4(1.0f);

        Configs configs = {};

        // Track a list of shapes which we render
        // Shapes are owned by this class. It simplifies client side a bit.
        std::vector<Shape*> shapes;

        /**
         * Releases all resources and states for the current Render data object
         */
        void releaseResources();

        Shape* getShapeById(unsigned int id);
        bool hasShapeById(unsigned int id);

    };

}
