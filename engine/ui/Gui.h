#pragma once

#include <MainApplication.h>

namespace xengine {

    /**
    * A base class for user interface component
    *
    * TODO: Revisit this class
    */
    class Gui : public MainThreadObserver
    {
    public:
        Gui(MainApplication* mainApp);
        virtual ~Gui();

        void onBeforeProcess() override;
        void onProcess() override;
        void onProcessEnd() override;

        void onCreate() override;
        void onDestroy() override;

    private:
        MainApplication* m_mainApplication = nullptr;
    };

}
