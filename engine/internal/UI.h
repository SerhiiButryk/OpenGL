#pragma once

namespace xengine {

    /**
     * Client application UI component interface
    */
    class UI {
    public:
        UI() = default;
        virtual ~UI() = default;

        virtual void onCreate() {}
        virtual void onRender() {}
        virtual void onDestroy() {}
    };

}
