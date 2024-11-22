#pragma once

#include <string>

namespace xengine {

    /**
    * Lifecycle component interface
    */
    class Lifecycle {
    public:

        Lifecycle() = default;
        virtual ~Lifecycle() = default;

        virtual void onCreate() {}
        virtual void onDestroy() {}
    };

    /**
     * Client UI interface
    */
    class UI {
    public:
        UI() = default;
        virtual ~UI() = default;

        virtual void onCreateUI() {}
        virtual void onRenderUI() {}
        virtual void onDestroyUI() {}
    };


    /**
    * Application client interface
    */
    class Application : public Lifecycle {
    public:
        Application() = default;
        virtual ~Application() = default;

        void onCreate() override {}
        void onDestroy() override {}

        virtual std::string getResourcePath() { return ""; }
        virtual UI* createUI() { return nullptr; }
    };

}
