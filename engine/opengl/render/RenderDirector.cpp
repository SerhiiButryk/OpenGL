#include "RenderDirector.h"

#include <stdexcept>
#include <common/Log.h>
#include <opengl/shapes/Line.h>
#include <opengl/shapes/Rectangle.h>

namespace xengine {

    ////////////////// RenderDirector //////////////////////////////////////////////////////////////////////////

    void RenderDirector::render() {

        m_renderer->setData(m_renderData);

        m_renderer->drawRectangle();

    }

    void RenderDirector::submit(Shape& shape) {

        // Create a buffer if it is not created
        createVertexBuffer();

        batch(shape);

        m_renderData->configs.vertexCount += shape.getVertexCount();

    }

    void RenderDirector::submit(Vertex &vertex) {

        // Create a buffer if it is not created
        createVertexBuffer();

        auto* destPointer = (Vertex*) m_renderData->configs.pointerStart;

        destPointer->position = vertex.position;
        destPointer->color = vertex.color;
        destPointer->texCoord = vertex.texCoord;
        destPointer->texIndex = vertex.texIndex;

        destPointer++;

        m_renderData->configs.pointerStart = destPointer;

        m_renderData->configs.vertexCount += 1;
    }


    ////////////////// RenderDirectorDebug //////////////////////////////////////////////////////////////////////////

    void RenderDirectorDebug::render() {

        m_renderer->setData(m_renderData);

        m_renderer->drawLine();

    }

    void RenderDirectorDebug::submit(Shape& shape) {

        // Create a buffer if it is not created
        createVertexBuffer();

        auto* rect = dynamic_cast<Rectangle*>(&shape);
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

            batch(line1);
            batch(line2);
            batch(line3);
            batch(line4);

            m_renderData->configs.vertexCount += line1.getVertexCount() * 4;

        } else {

            throw std::runtime_error("Not support this type of shape yet");
        }

    }

    void RenderDirectorDebug::submit(Vertex &vertex) {

    }
}
