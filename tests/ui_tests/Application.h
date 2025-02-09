#pragma once

#include "public/XEngine.h"

namespace test {
    /**
     *  Our client application
     */
    class Application : public xengine::Application {
    public:
        Application();
        ~Application() override = default;

        void onCreate() override;
        void onDestroy() override {}

        std::string getResourcePath() override;

        xengine::WindowConfigs onCreateWindow() override;

        int getWidth() const { return width; }
        int getHeight() const { return height; }

    private:
        int width = 1280;
        int height = 720;
        const char* title = "Test app";
        void* testMenuUI = nullptr;
    };
}