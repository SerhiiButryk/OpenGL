#pragma once

#include <opengl/Camera.h>
#include <opengl/IndexBuffer.h>
#include <opengl/Shader.h>
#include <opengl/Textures.h>
#include <opengl/VertexArray.h>
#include <opengl/shapes/Rectangle.h>

namespace xengine {

    static constexpr unsigned int DEFAULT_VERTEX_BUFF_SIZE = 100;
    static constexpr unsigned int DEFAULT_INDEX_BUFF_SIZE = 100;

    // A per object data for our render[
    struct Object {

        Shape* shape = nullptr;
        Shader* shader = nullptr;
        Texture* texture = nullptr;

        glm::mat4 tansform = glm::mat4(1.0f);

        void* drawBuffer = nullptr; // actual data buffer
        void* drawBufferPointer = nullptr; // pointer to the next vertex place in the buffer

        uint32_t elementCount {}; // number of vertices to draw

        uint32_t indexBufferSizeDefault = DEFAULT_INDEX_BUFF_SIZE;

        VertexArray* vertexArray = nullptr;
        VertexBuffer* vertexBuffer = nullptr;
        IndexBuffer* indexBuffer = nullptr;
    };

}
