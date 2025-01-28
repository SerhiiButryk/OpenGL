#pragma once

#include "RenderDirectorBase.h"

namespace xengine {

    class RenderDirector : public RenderDirectorBase
    {
    public:

        void submit(Shape& shape) override;
        void submit(Vertex &vertex) override;

        void render() override;

    };

    class RenderDirectorDebug : public RenderDirector {
    public:

        void render() override;

        void submit(Shape& shape) override;
        void submit(Vertex &vertex) override;

    };

}