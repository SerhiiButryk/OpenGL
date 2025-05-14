#pragma once

#include "RenderGLBase.h"

namespace xengine {

    class RenderGL : public RenderGLBase
    {
    public:

        void submit(RenderData::Objects* object) override;

        void render() override;

    };

    class RenderGLDebug : public RenderGL {
    public:

        void submit(RenderData::Objects* object) override;

        void render() override;

    };

}