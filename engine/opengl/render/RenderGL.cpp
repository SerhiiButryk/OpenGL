#include "RenderGL.h"

#include <stdexcept>
#include <common/Log.h>
#include <opengl/shapes/Line.h>
#include <opengl/shapes/Rectangle.h>

namespace xengine {

    ////////////////////////////////////////////////////////////////////////////////////////////

    void RenderGL::render() {

        m_renderer->setData(m_renderData);

        m_renderer->drawRectangle(m_renderData->tansform);

    }

    void RenderGL::submit(Shape* shape) {

        // Create a buffer if it is not created
        createVertexBuffer();

        batch(shape);

        m_renderData->configs.vertexCount += shape->getVertexCount();

        m_renderData->shapes.push_back(shape);

    }

    ////////////////////////////////////////////////////////////////////////////////////////////

    void RenderGLDebug::render() {

        m_renderer->setData(m_renderData);

        m_renderer->drawLine(m_renderData->tansform);

    }

    void RenderGLDebug::submit(Shape* shape) {

        // Create a buffer if it is not created
        createVertexBuffer();

        auto rect = dynamic_cast<Rectangle*>(shape);
        if (rect != nullptr) {

            auto centerPoint = rect->getCoord();
            auto width = rect->getWidth();
            auto height = rect->getHeight();

            Line line1({ centerPoint.x - width * 0.5f, centerPoint.y - height * 0.5f, 0.0f },
                { centerPoint.x + width * 0.5f, centerPoint.y - height * 0.5f, 0.0f });

            Line line2({ centerPoint.x + width * 0.5f, centerPoint.y - height * 0.5f, 0.0f },
                { centerPoint.x + width * 0.5f, centerPoint.y + height * 0.5f, 0.0f });

            Line line3({ centerPoint.x + width * 0.5f, centerPoint.y + height * 0.5f, 0.0f },
                { centerPoint.x - width * 0.5f, centerPoint.y + height * 0.5f, 0.0f });

            Line line4({ centerPoint.x - width * 0.5f, centerPoint.y + height * 0.5f, 0.0f },
                { centerPoint.x - width * 0.5f, centerPoint.y - height * 0.5f, 0.0f });

            batch(&line1);
            batch(&line2);
            batch(&line3);
            batch(&line4);

            m_renderData->configs.vertexCount += line1.getVertexCount() * 4;

        } else {

            throw std::runtime_error("Not support this type of shape yet");
        }

    }

}
