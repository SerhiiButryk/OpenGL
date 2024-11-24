#pragma once

#include "internal/Lifecycle.h"

namespace xengine {
    /**
     *  Main thread render observer class
     */
    class MainThreadObserver : public Lifecycle {
    public:
        MainThreadObserver() = default;
        ~MainThreadObserver() override = default;

        virtual void onBeforeProcess() {}
        virtual void onProcess() {}
        virtual void onProcessEnd() {}

        virtual void onCreate() {}
        virtual void onDestroy() {}
    };
}
