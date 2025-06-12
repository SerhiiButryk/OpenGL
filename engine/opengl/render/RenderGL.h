#pragma once

#include "RenderGLBase.h"

namespace xengine {

    class RenderGL : public RenderGLBase
    {
    public:
        ~RenderGL() override;

        void submit(Object* object) override;

        void render() override;

    };

    class RenderGLDebug : public RenderGL {
    public:

        ~RenderGLDebug() override;

        void submit(Object* object) override;

        void render() override;

    };

}