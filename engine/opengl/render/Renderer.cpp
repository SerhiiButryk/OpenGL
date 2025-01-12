#include "Renderer.h"

#include "opengl/shapes/Shape.h"

namespace xengine {

    void Renderer::clearScreen(glm::vec4 color) {
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::drawRectangle() const {

        if (m_renderData->vertexBuffer->isDynamic()) {
            // If buffer is dynamic we update the vertex buffer
            m_renderData->vertexBuffer->update(
                (float*) m_renderData->configs.drawBuffer,
                VERTEX_TOTAL_SIZE(m_renderData->configs.vertexCount));
        }

        auto* va = m_renderData->vertexArray;
        auto* ib = m_renderData->indexBuffer;
        auto* shader = m_renderData->shader;

        /* Bind everything before making a draw call */

        shader->bind();
        va->bind();
        ib->bind();

        /* Send a draw command */

        glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr);

    }

    void Renderer::drawLine() const {

        uint32_t count = m_renderData->configs.vertexCount;

        // TODO: Might be a part of RenderCommand
        m_renderData->vertexBuffer->update((float*) m_renderData->configs.drawBuffer, VERTEX_TOTAL_SIZE(count));

        auto* va = m_renderData->vertexArray;
        auto* shader = m_renderData->shader;

        shader->bind();
        va->bind();

        // TODO: Doesn't work on Ubuntu
        // GLfloat aliasedLineRange[2];
        // glGetFloatv(GL_LINE_WIDTH_RANGE, aliasedLineRange);
        // glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, aliasedLineRange);
        // glLineWidth(aliasedLineRange[1]);

        /* Send a draw command */

        glDrawArrays(GL_LINES, 0, count);

    }

}
