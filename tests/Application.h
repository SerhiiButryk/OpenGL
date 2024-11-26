#pragma once

#include "public/XEngine.h"

namespace test {
    /**
     *  Our application
     */
    class Application : public xengine::Application {
    public:
        Application() = default;
        ~Application() override = default;

        void onCreate() override {}
        void onDestroy() override {}

        std::string getResourcePath() override;

        xengine::UI* createUI() override;
    };
}