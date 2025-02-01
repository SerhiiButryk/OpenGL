#include "AppUI.h"

namespace xengine {

    ApplicationUI::ApplicationUI() {
    }

    ApplicationUI::~ApplicationUI() {
        delete m_clientUI;
    }

    void ApplicationUI::onCreate() {

        if (m_clientUI == nullptr) {
            m_clientUI = m_clientApp->onCreateUI();
        }

        m_clientUI->onCreate();

    }

    void ApplicationUI::onDestroy() {

        m_clientUI->onDestroy();

    }

    void ApplicationUI::onProcess(void* app) {

        m_clientUI->onDraw();
    }

}
