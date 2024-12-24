#pragma once

#include <internal/UI.h>
#include <internal/MainThreadObserver.h>

namespace xengine {

    /**
    * Application UI component.
    *
    * This is a part which manages and knows about our client UI.
    */
    class ApplicationUI : public MainThreadObserver
    {
    public:
        explicit ApplicationUI();
        ~ApplicationUI() override;

        // Get called by Main thread
        void onStart() override;
        void onProcess(void* app) override;
        void onEnd() override;

        void setClientUI(UI* ui) { m_clientUI = ui; }

    private:
        UI* m_clientUI = nullptr;
    };
}
