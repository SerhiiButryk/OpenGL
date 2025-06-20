#pragma once

#include "RenderGLBase.h"

namespace xengine {

    class RenderGL : public RenderGLBase
    {
    public:
        ~RenderGL() override;

        void submit(Object* object) override;

        void batchStart();
        void batchSubmit(Object*);
        void batchEnd();

        void render() override;

    private:
        // Used for batching mode
        Object* m_groupObject = nullptr;
        // Whether we are in batching mode
        bool m_isBatchStarted = false;

    };

}