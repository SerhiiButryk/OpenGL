#pragma once

#include "internal/Lifecycle.h"
#include "internal/InternalApplication.h"
#include "internal/UI.h"
#include "window/WindowConfigs.h"

#include <string>

namespace xengine {

    /**
    * Application client interface
    */
    class Application : public Lifecycle {
    public:
        Application() = default;
        ~Application() override = default;

        /**
         * Callback to allocate resources
         */
        void onCreate() override {}

        /**
         * Callback to free resources
         */
        void onDestroy() override {}

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
         * @return  resource path
         */
        virtual std::string getResourcePath() { return ""; }

        void setMainApplication(InternalApplication* app) { m_mainApplication = app; }
        auto* getMainApplication() const { return m_mainApplication; }

    protected:
        InternalApplication* m_mainApplication = nullptr;
    };

}