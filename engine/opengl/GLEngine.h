#pragma once

namespace xengine {

    /*
     * A class which manages global engine configurations
     * and states of Graphic Library under the hood.
     *
     */
    class GLEngine {
    public:
        /* Init library and components */
        static bool initEngine();

        static void setViewPorts(int bufferWidth, int bufferHeight);

        // Log GL information
        static void printInfo();

        // The caller owns the string and it should call free() in the end
        static char* getGLInfoAsString();
        static char* getVendorInfoAsString();
        static char* getRendererInfoAsString();

        static void setDebugCallback();

        static void setBlending(bool enable);
        static void setBlendingMode();

    private:
        static inline bool IS_INITIALIZED = false;
        static inline bool CAN_BE_USED = false;
    };

}
