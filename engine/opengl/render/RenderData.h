#pragma once

#include <opengl/Camera.h>
#include <opengl/IndexBuffer.h>
#include <opengl/Shader.h>
#include <opengl/Textures.h>
#include <opengl/VertexArray.h>
#include <opengl/shapes/Shape.h>

namespace xengine {

    static constexpr unsigned int DEFAULT_VERTEX_BUFF_SIZE = 100;
    static constexpr unsigned int DEFAULT_INDEX_BUFF_SIZE = 50;

    struct OpenGLRenderData {

        Shader* shader = nullptr;
        Texture* texture = nullptr;

        Vertex* drawBuffer = nullptr; // actual data buffer
        size_t drawBufferSize = 0;
        size_t elementIndex = 0; // pointer to the next vertex place in the buffer

        uint32_t elementCount {}; // number of vertices to draw

        VertexArray* vertexArray = nullptr;
        VertexBuffer* vertexBuffer = nullptr;
        IndexBuffer* indexBuffer = nullptr;

        void free() {

            if (vertexArray) {
                vertexArray->unbind();
            }

            if (shader) {
                shader->unBind();
            }

            if (indexBuffer) {
                indexBuffer->unbind();
            }

            if (vertexBuffer) {
                vertexBuffer->unbind();
            }

            if (drawBuffer) {

                delete [] (float*) drawBuffer;

                drawBuffer = nullptr;
                elementIndex = 0;
            }

            delete vertexArray;
            delete vertexBuffer;
            delete indexBuffer;
            delete shader;
            delete texture;
        }
    };

    // Object which stores renderer data
    struct Object : OpenGLRenderData {

        Shape* shape = nullptr;
        size_t shapesCount = 0;

        Shape* getShape() {
            return shape;
        }

        void free() {
            OpenGLRenderData::free();
            delete shape;
        }

        void setMaterial(const glm::mat4& modelMatrix, const std::string& shaderPath, const std::string& texturePath);
    };

}
