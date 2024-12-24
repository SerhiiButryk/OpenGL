#include "AppUI.h"

namespace xengine {

    ApplicationUI::ApplicationUI() {
    }

    ApplicationUI::~ApplicationUI() {
        if (m_clientUI != nullptr) {
            delete m_clientUI;
        }
    }

    void ApplicationUI::onStart() {
        m_clientUI->onCreate();
    }

    void ApplicationUI::onProcess(void* app) {
        m_clientUI->onDraw();
    }

    void ApplicationUI::onEnd() {
        m_clientUI->onDestroy();
    }

}
