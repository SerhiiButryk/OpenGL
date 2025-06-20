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

            if (object->drawBufferSize == 0) {
                LOG_ERROR("Renderer::setCommonConfigs: draw buffer size is not set");
            }

            object->vertexBuffer->update(
                (float*) object->drawBuffer,
                VERTEX_BYTES_SIZE(object->drawBufferSize));
        }
    }

    void Renderer::drawRectangle(const Object* object) {

        setCommonConfigs(object);

        auto* va = object->vertexArray;
        auto* ib = object->indexBuffer;
        auto* shader = object->shader;

        /* Bind everything before making a draw call */

        shader->bind();
        va->bind();
        ib->bind();

        LOG_DEBUG("Renderer::drawRectangle() Draw elements = '{}'", object->elementCount);

        /* Send a draw command */

        glDrawElements(GL_TRIANGLES, object->elementCount, GL_UNSIGNED_INT, nullptr);

        /* Unbind to be safe  */

        shader->unBind();
        va->unbind();
        ib->unbind();

    }

}
