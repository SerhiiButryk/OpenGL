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
        explicit ApplicationUI(UI* ui);
        ~ApplicationUI() override = default;

        // Get called by Main thread
        void onBeforeProcess() override;
        void onProcess() override;
        void onProcessEnd() override;

    private:
        UI* m_clientUI = nullptr;
    };
}
