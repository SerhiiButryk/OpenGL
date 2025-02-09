#pragma once

namespace xengine {

    /**
     * Client user interface component
    */
    class UIComponent : public Layer {
    public:
        UIComponent() = default;
        ~UIComponent() override = default;

        /**
         * Callback to receive system or application events
         */
        bool onEvent(const Event &event) override { return false; }

        /**
        * Callback to attach this component
        */
        void onAttach() override {}

        /**
       * Callback to detach this component
       */
        void onDetach() override {}

        /**
         * Callback to draw this user interface
         * Should be overridden
         */
        void onDraw() override = 0;

    };

}
