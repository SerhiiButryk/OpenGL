#pragma once

#include "RenderDirectorBase.h"

namespace xengine {

    class RenderDirector : public RenderDirectorBase
    {
    public:

        void addShape(Shape& shape) override;

        void render() override;

    };

    class RenderDirectorDebug : public RenderDirector {
    public:

        void render() override;

        void addShape(Shape& shape) override;

    };

}