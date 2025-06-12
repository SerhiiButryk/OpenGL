#include "Renderer.h"

#include <common/Log.h>
#include "opengl/shapes/Shape.h"

namespace xengine {

    void Renderer::clearScreen(glm::vec4 color) {
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::setCommonConfigs(const Object* object) {
        // If the buffer is dynamic we update the vertex buffer
        if (object->vertexBuffer->isDynamic()) {

            if (!object->drawBuffer) {
                LOG_ERROR("Renderer::setCommonConfigs: drawBuffer is not set");
            }

            if (object->elementCount == 0) {
                LOG_ERROR("Renderer::setCommonConfigs: vertex count is not set");
            }

            object->vertexBuffer->update(
                (float*) object->drawBuffer,
                VERTEX_TOTAL_SIZE(object->elementCount));
        }
    }

    void Renderer::drawRectangle(const Object* object) {

        LOG_DEBUG("Renderer::drawRectangle() obj = '{:p}' START", fmt::ptr(&object));

        setCommonConfigs(object);

        auto* va = object->vertexArray;
        auto* ib = object->indexBuffer;
        auto* shader = object->shader;

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

        LOG_DEBUG("Renderer::drawRectangle() obj = '{:p}' END", fmt::ptr(&object));

    }

    void Renderer::drawLine(const Object* object) {

        setCommonConfigs(object);

        // auto* va = object->vertexArray;
        // auto* shader = object->shader;

        // shader->bind();
        // va->bind();

        // TODO: Doesn't work on Ubuntu
        // GLfloat aliasedLineRange[2];
        // glGetFloatv(GL_LINE_WIDTH_RANGE, aliasedLineRange);
        // glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, aliasedLineRange);
        // glLineWidth(aliasedLineRange[1]);

        /* Send a draw command */

        // uint32_t count = m_renderData->configs.vertexCount;

        // glDrawArrays(GL_LINES, 0, count);

    }

}
