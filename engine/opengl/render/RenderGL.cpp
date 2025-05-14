#include "RenderGL.h"

#include <common/Log.h>
#include <opengl/shapes/Line.h>

namespace xengine {

    ////////////////////////////////////////////////////////////////////////////////////////////

    void RenderGL::render() {

        m_impl->setData(m_renderData);

        for (auto && object : m_objectsList) {

            LOG_DEBUG("RenderGL::render() obj = '{:p}'", fmt::ptr(object));

            m_impl->drawRectangle(*object);
        }

    }

    void RenderGL::submit(RenderData::Objects* object) {

        LOG_INFO("RenderGL::submit() obj = '{:p}'", fmt::ptr(object));

        // Create a buffer if it is not created
        createVertexBuffer();

        // Batch to draw buffer
        batch(object->shape);

        m_renderData->configs.vertexCount += object->shape->getVertexCount();

        // Call to create or configure VAO, VBO ets...
        setPipeline(object);

        m_objectsList.push_back(object);

    }

    ////////////////////////////////////////////////////////////////////////////////////////////

    void RenderGLDebug::render() {

        // m_impl->setData(m_renderData);
        //
        // m_impl->drawLine(m_renderData->tansform);

    }

    void RenderGLDebug::submit(RenderData::Objects* object) {

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
