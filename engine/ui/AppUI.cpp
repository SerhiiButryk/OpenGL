#include "AppUI.h"

namespace xengine {

    ApplicationUI::ApplicationUI() {
    }

    ApplicationUI::~ApplicationUI() {
        delete m_clientUI;
    }

    void ApplicationUI::onStart() {

        if (m_clientUI == nullptr) {
            m_clientUI = m_clientApp->onCreateUI();
        }

        m_clientUI->onCreate();
    }

    void ApplicationUI::onProcess(void* app) {
        m_clientUI->onDraw();
    }

    void ApplicationUI::onEnd() {
        m_clientUI->onDestroy();
    }

}
