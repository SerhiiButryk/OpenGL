#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "Textures.h"
#include "VertexArray.h"
#include "shapes/Shape.h"

namespace xengine {
    class Renderer;

    class RenderCommand {
    public:
        void begin();
        void prepareShader(const std::string& filePath, int w, int h);
        void prepareTexture(const std::string& filePath);
        void end();
        void clear();

        void execute(float* buffer);

    private:
        Renderer* renderer;

        Shader* shader;
        VertexArray* vertexArray;
        VertexBuffer* vertexBuffer;
        IndexBuffer* indexBuffer;
        Texture* texture;
    };

    class Renderer
    {
    public:

        void clean(float red, float green, float blue, float alpha) const;
        void clearStates(VertexArray* va, Shader* shader, VertexBuffer* vb, IndexBuffer* ib) const;

        void draw(const VertexArray& va, const IndexBuffer& id, const Shader& shader) const;

        void setMVPMatrix(const std::string& name, Shader* shader, int windowWidth, int windowHeight) const;

        BufferLayout getLayoutSpecificationForVertex();
        void prepareIndexBuffer(IndexBuffer* ib) const;
    };
}
