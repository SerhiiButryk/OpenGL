#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "Textures.h"
#include "VertexArray.h"
#include "shapes/Rectangle.h"

namespace xengine {

    /**
     * A command to render
     */
    class RenderCommand {
    public:

        struct Configs {
            int width {}, height {}; // window size information in pixels
            uint32_t vertexCount {}; // number of vertices
            uint32_t indexBufferMaxSize {}; // max number of indecision which we can have
            float* drawBuffer = nullptr; // actual data buffer
        };

        void setConfigs(Configs configs);

        void setShape(Rectangle rectangle);

        Shader* shader = nullptr;
        VertexArray* vertexArray = nullptr;
        VertexBuffer* vertexBuffer = nullptr;
        IndexBuffer* indexBuffer = nullptr;
        Texture* texture = nullptr;

        Configs configs = {};
    };

    /**
     * Main Renderer API
     */
    class Renderer
    {
    public:

        static void clearScreen(glm::vec4 color);
        void clearStates() const;

        void draw(const VertexArray& va, const IndexBuffer& id, const Shader& shader) const;

        void setMVPMatrix(const std::string& name, Shader* shader, int windowWidth, int windowHeight) const;

        void prepareIndexBuffer(IndexBuffer* ib, uint32_t maxCount) const;

        bool executeCurrentCommand();

        void begin(RenderCommand* command);

        void prepareShader(const std::string& filePath);
        void prepareTexture(const std::string& filePath, const std::string& textureName);
        void prepareMVPMatrix(const std::string& name);

        void end();

        void clear();

        auto* getCurrentCommand() const { return m_command; };

    private:
        RenderCommand* m_command = nullptr;
    };
}
