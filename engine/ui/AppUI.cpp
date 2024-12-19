#include "AppUI.h"

namespace xengine {

    ApplicationUI::ApplicationUI(UI* ui) : m_clientUI(ui) {
    }

    void ApplicationUI::onBeforeProcess() {
        m_clientUI->onCreate();
    }

    void ApplicationUI::onProcess() {
        m_clientUI->onRender();
    }

    void ApplicationUI::onProcessEnd() {
        m_clientUI->onDestroy();
    }

}
