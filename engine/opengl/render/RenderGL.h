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

}