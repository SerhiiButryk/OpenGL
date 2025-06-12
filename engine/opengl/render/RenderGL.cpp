#include "RenderGL.h"

#include <common/Log.h>
#include <opengl/shapes/Line.h>

namespace xengine {

    ////////////////////////////////////////////////////////////////////////////////////////////

    RenderGL::~RenderGL() {
        releaseObjects();
    }

    void RenderGL::render() {

        // Process the object list

        for (auto && object : m_objectsList) {

            LOG_DEBUG("RenderGL::render() rendering obj = '{:p}'", fmt::ptr(object));

            // Update buffer if shape is invalid
            if (object->shape->isInvalid()) {

                // Batch this shape into draw buffer
                batch(object);

                // Call to create VAO, VBO ets... for this object
                createGLBuffers(object);

                object->shape->reset();
            }

            m_impl->drawRectangle(object);
        }

    }

    void RenderGL::submit(Object* object) {

        // Create a buffer if it is not created
        createDrawBuffer(object);

        // Batch this shape into draw buffer
        batch(object);

        // Call to create VAO, VBO ets... for this object
        createGLBuffers(object);

        m_objectsList.push_back(object);

        LOG_DEBUG("RenderGL::submit() done, vertex count = '{}', new obj = '{:p}', total objects = '{}'",
            object->elementCount, fmt::ptr(object), m_objectsList.size());

    }

    ////////////////////////////////////////////////////////////////////////////////////////////

    RenderGLDebug::~RenderGLDebug() {
        releaseObjects();
    }

    void RenderGLDebug::render() {

        // m_impl->setData(m_renderData);
        //
        // m_impl->drawLine(m_renderData->tansform);

    }

    void RenderGLDebug::submit(Object* object) {

        // // Create a buffer if it is not created
        // createVertexBuffer();
        //
        // auto rect = dynamic_cast<Rectangle*>(shape);
        // if (rect != nullptr) {
        //
        //     auto centerPoint = rect->getCoord();
        //     auto width = rect->getWidth();
        //     auto height = rect->getHeight();
        //
        //     Line line1({ centerPoint.x - width * 0.5f, centerPoint.y - height * 0.5f, 0.0f },
        //         { centerPoint.x + width * 0.5f, centerPoint.y - height * 0.5f, 0.0f });
        //
        //     Line line2({ centerPoint.x + width * 0.5f, centerPoint.y - height * 0.5f, 0.0f },
        //         { centerPoint.x + width * 0.5f, centerPoint.y + height * 0.5f, 0.0f });
        //
        //     Line line3({ centerPoint.x + width * 0.5f, centerPoint.y + height * 0.5f, 0.0f },
        //         { centerPoint.x - width * 0.5f, centerPoint.y + height * 0.5f, 0.0f });
        //
        //     Line line4({ centerPoint.x - width * 0.5f, centerPoint.y + height * 0.5f, 0.0f },
        //         { centerPoint.x - width * 0.5f, centerPoint.y - height * 0.5f, 0.0f });
        //
        //     batch(&line1);
        //     batch(&line2);
        //     batch(&line3);
        //     batch(&line4);
        //
        //     m_renderData->configs.vertexCount += line1.getVertexCount() * 4;
        //
        // } else {
        //
        //     throw std::runtime_error("Not support this type of shape yet");
        // }

    }

}
