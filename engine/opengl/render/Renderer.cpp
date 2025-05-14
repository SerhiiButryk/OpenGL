#include "Renderer.h"

#include <common/Log.h>

#include "opengl/shapes/Shape.h"

namespace xengine {

    void Renderer::clearScreen(glm::vec4 color) {
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::setCommonConfigs(const RenderData::Objects& object) {

        if (object.vertexBuffer->isDynamic()) {
            // If the buffer is dynamic we update the vertex buffer
            object.vertexBuffer->update(
                (float*) m_renderData->configs.drawBuffer,
                VERTEX_TOTAL_SIZE(m_renderData->configs.vertexCount));
        }

        auto* shader = object.shader;
        shader->bind();

        // TODO: Get rid of hardcoding
        // Set camera matrix
        shader->setUniformMat("u_ViewProjMatrix", m_renderData->configs.viewProjMatrix);

        // Set transformation for our object
        shader->setUniformMat("u_ModelMatrix", object.tansform);

    }

    void Renderer::drawRectangle(const RenderData::Objects& object) {

        LOG_DEBUG("Renderer::drawRectangle() obj = '{:p}' IN", fmt::ptr(&object));

        setCommonConfigs(object);

        auto* va = object.vertexArray;
        auto* ib = object.indexBuffer;
        auto* shader = object.shader;

        /* Bind everything before making a draw call */

        shader->bind();
        va->bind();
        ib->bind();

        /* Send a draw command */

        glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr);

        /* Unbind to be safe  */

        shader->unBind();
        va->unbind();
        ib->unbind();

        LOG_DEBUG("Renderer::drawRectangle() obj = '{:p}' OUT", fmt::ptr(&object));

    }

    void Renderer::drawLine(const RenderData::Objects& object) {

        setCommonConfigs(object);

        auto* va = object.vertexArray;
        auto* shader = object.shader;

        shader->bind();
        va->bind();

        // TODO: Doesn't work on Ubuntu
        // GLfloat aliasedLineRange[2];
        // glGetFloatv(GL_LINE_WIDTH_RANGE, aliasedLineRange);
        // glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, aliasedLineRange);
        // glLineWidth(aliasedLineRange[1]);

        /* Send a draw command */

        uint32_t count = m_renderData->configs.vertexCount;

        glDrawArrays(GL_LINES, 0, count);

    }

}
