#include "DecoratorUI.h"

#include <common/Log.h>
#include <external/GUIHelper.h>

namespace xengine {

    DecoratorUI::DecoratorUI(void* window): m_nativeWindow(window) {
    }

    DecoratorUI::~DecoratorUI() {

    }

    void DecoratorUI::onAttach() {

        LOG_INFO("DecoratorUI::onAttach init decorator layer");

        if (!m_isAttached) {
            GUIHelper::init(m_nativeWindow);
            m_isAttached = true;
        } else {

            LOG_ERROR("DecoratorUI::onAttach layer already attached");

#ifndef UNIT_TESTS
            throw std::runtime_error("DecoratorUI::onAttach layer already attached");
#endif
        }
    }

    void DecoratorUI::onDetach() {

        LOG_INFO("DecoratorUI::onDetach release decorator layer");

        if (m_isAttached) {
            GUIHelper::destroy();
            m_isAttached = false;
        } else {

            LOG_ERROR("DecoratorUI::onDetach layer not attached");

#ifndef UNIT_TESTS
            throw std::runtime_error(std::string("DecoratorUI::onDetach layer not attached"));
#endif
        }
    }

    void DecoratorUI::onDraw() {
        // No-op
    }

}
