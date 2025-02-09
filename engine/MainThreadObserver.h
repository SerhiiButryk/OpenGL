#pragma once

namespace xengine {

    /**
     *  Main thread observer class
     */
    class MainThreadObserver {
    public:
        MainThreadObserver() = default;
        virtual ~MainThreadObserver() = default;

        virtual void onStart() {}
        virtual void onProcess(void* app) {}
        virtual void onEnd() {}
    };
}
