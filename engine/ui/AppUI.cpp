#include "AppUI.h"

namespace xengine {

    AppUI::AppUI(UI* ui) : m_clientUI(ui) {
    }

    void AppUI::onBeforeProcess() {
        m_clientUI->onCreate();
    }

    void AppUI::onProcess() {
        m_clientUI->onRender();
    }

    void AppUI::onProcessEnd() {
        m_clientUI->onDestroy();
    }

}
