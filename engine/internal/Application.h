#pragma once

#include "internal/Lifecycle.h"
#include "internal/InternalApplication.h"
#include "internal/UI.h"

#include <string>

namespace xengine {

    /**
    * Application client interface
    */
    class Application : public Lifecycle {
    public:
        Application() = default;
        ~Application() override = default;

        void onCreate() override {}
        void onDestroy() override {}

        virtual std::string getResourcePath() { return ""; }
        virtual UI* createUI() { return nullptr; }

        void setMainApplication(InternalApplication* app) { m_mainApplication = app; }
        InternalApplication* getMainApplication() const { return m_mainApplication; }

    protected:
        InternalApplication* m_mainApplication = nullptr;
    };

}