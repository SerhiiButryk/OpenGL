#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "Textures.h"
#include "VertexArray.h"

namespace xengine {

    class Renderer;

    class RenderCommand {
    public:

        struct CommandConfigs {
            int width, height; // window size in pixels
            uint32_t vertexCount;
            float* newBuffer = nullptr;
        };

        void begin(Renderer* renderer);

        void prepareShader(const std::string& filePath);
        void prepareTexture(const std::string& filePath, const std::string& textureName);
        void prepareMVPMatrix(const std::string& name);

        void end();

        void clear();

        // void execute(float* buffer);

        void setConfigs(CommandConfigs configs);

        Renderer* renderer = nullptr;

        Shader* shader = nullptr;
        VertexArray* vertexArray = nullptr;
        VertexBuffer* vertexBuffer = nullptr;
        IndexBuffer* indexBuffer = nullptr;
        Texture* texture = nullptr;

        CommandConfigs configs = {};
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

        void execute(const RenderCommand &command);
    };
}
