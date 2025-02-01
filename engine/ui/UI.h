#pragma once

namespace xengine {

    /**
     * Client user interface component
    */
    class UI {
    public:
        UI() = default;
        virtual ~UI() = default;

        /**
         * Callback to allocate resources
         */
        virtual void onCreate() {}

        /**
         * Callback to free resources
         */
        virtual void onDestroy() {}

        /**
         * Callback to draw this user interface
         */
        virtual void onDraw() {}

    };

}
