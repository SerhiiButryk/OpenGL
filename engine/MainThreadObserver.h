#pragma once

#include <app/Lifecycle.h>

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

        /**
         * Called when thread is created. One time call at process startup
         */
        void onCreate() override {}

        /**
         * Called when thread is stopped. One time call at process end.
         */
        void onDestroy() override {}
    };
}
