#pragma once

#include "RenderDirectorBase.h"

namespace xengine {

    class RenderDirector : public RenderDirectorBase
    {
    public:

        void submit(Shape* shape) override;

        void render() override;

    };

    class RenderDirectorDebug : public RenderDirector {
    public:

        void submit(Shape* shape) override;

        void render() override;

    };

}