#pragma once

#include "RenderData.h"

namespace xengine {

    void RenderData::releaseResources() {

        if (vertexArray) {
            vertexArray->unbind();
        }

        if (shader) {
            shader->unBind();
        }

        if (indexBuffer) {
            indexBuffer->unbind();
        }

        if (vertexBuffer) {
            vertexBuffer->unbind();
        }

        delete vertexArray;
        delete vertexBuffer;
        delete indexBuffer;
        delete shader;
        delete texture;
        delete camera;

        delete [] (float*) configs.drawBuffer;
        configs.drawBuffer = nullptr;
        configs.pointerStart = nullptr;

    }

}