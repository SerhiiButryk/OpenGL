#pragma once

#include "Lifecycle.h"

namespace xengine {
    /**
     *  Main thread observer class
     */
    class MainThreadObserver : public Lifecycle {
    public:
        MainThreadObserver() = default;
        ~MainThreadObserver() override = default;

        virtual void onStart() {}
        virtual void onProcess(void* app) {}
        virtual void onEnd() {}

        void onCreate() override {}
        void onDestroy() override {}
    };
}
