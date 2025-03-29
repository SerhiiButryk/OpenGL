#pragma once

namespace xengine {

    /**
     *  Helper for ImGUI library
     *  Handle library specific configuration and setup
     */

    class GUIHelper
    {
    public:

        static void init(void* w);
        static void destroy();

        static void beginGUI();
        static void endGUI();
    };

}