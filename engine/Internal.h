#pragma once

#include "Interfaces.h"

namespace xengine {
    /**
    * Internal application class
    */
    class InternalApplication : public Lifecycle {
    public:
        InternalApplication() = default;
        virtual ~InternalApplication() = default;

        void onCreate() override {}
        void onDestroy() override {}
    };

    /**
     *  Main thread render observer class
     */
    class MainThreadObserver : public Lifecycle {
    public:
        MainThreadObserver() = default;
        virtual ~MainThreadObserver() = default;

        virtual void onBeforeProcess() {}
        virtual void onProcess() {}
        virtual void onProcessEnd() {}

        virtual void onCreate() {}
        virtual void onDestroy() {}
    };
}
