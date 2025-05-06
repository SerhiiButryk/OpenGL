#pragma once

#include "RenderData.h"

#include <algorithm>

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
        // Camera is not owned by this class
        // delete camera

        delete [] (float*) configs.drawBuffer;

        configs = {};

        for (auto && shape : shapes) {
            delete shape;
        }

        shapes.clear();

    }

    Shape* RenderData::getShapeById(unsigned int id) {

        auto it = std::find_if (shapes.begin(), shapes.end(), [id](Shape* shape) {
            return shape->getID() == id;
        });

        return (it == shapes.end()) ? nullptr : *it;
    }

    bool RenderData::hasShapeById(unsigned int id) {
        return getShapeById(id) != nullptr;
    }

}