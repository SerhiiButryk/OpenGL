#pragma once

#include <internal/UI.h>
#include <internal/MainThreadObserver.h>

namespace xengine {

    class AppUI : public MainThreadObserver
    {
    public:
        explicit AppUI(UI* ui);
        ~AppUI() override = default;

        void onBeforeProcess() override;
        void onProcess() override;
        void onProcessEnd() override;

    private:
        UI* m_clientUI = nullptr;
    };
}
