#pragma once

#include <app/Lifecycle.h>
#include <app/InternalApplication.h>
#include <ui/UI.h>
#include <window/WindowConfigs.h>

#include <string>

namespace xengine {

    /**
    * Application client interface
    */
    class Application : public Lifecycle, public EventListener {
    public:
        Application() = default;
        ~Application() override = default;

        /**
         * Callback to allocate resources
         */
        void onCreate() override = 0;

        /**
         * Callback to free resources
         */
        void onDestroy() override = 0;

        /**
         * Override to set application UI
         * @return new application UI
         */
        virtual UI* onCreateUI() { return nullptr; }

        /**
         * Override to set window configurations
         * @return new window configurations
         */
        virtual WindowConfigs onCreateWindow() { return { 0, 0, "" }; }

        /**
         * Override to set resource path
         * @return new resource path
         */
        virtual std::string getResourcePath() { return ""; }

        /**
         * Set a reference to internal application class controlled by the engine side
         */
        void setMainApplication(InternalApplication* app) { m_mainApplication = app; }

        /**
         * Get a window native pointer
         */
        auto* getNativeWindow() const { return m_mainApplication->getWindow(); }

        /**
         * Callback to receive new events from application or window
         */
        bool onEvent(const Event &event) override {
            return false;
        }

        /**
         * Get frame update time
         */
        auto getFrameDeltaTime() const { return m_mainApplication->getFrameDeltaTime(); }

    protected:
        InternalApplication* m_mainApplication = nullptr;
    };

}