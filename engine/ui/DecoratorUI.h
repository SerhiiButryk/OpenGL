#pragma once

#include <memory>
#include <common/Log.h>
#include <opengl/shapes/Color.h>

#include "UIComponent.h"

namespace xengine {

    /**
    * Internal application UI component.
    * This is the first layer of our application.
    */
    class DecoratorUI : public UIComponent
    {
    public:
        explicit DecoratorUI(void*);
        ~DecoratorUI() override;

        void onAttach() override;

        void onDetach() override;

        void onDraw() override;

        void onDrawUI() override;

    private:
        // Ref to window implementation
        void* m_nativeWindow;
        bool m_isAttached = false;

        std::unique_ptr<char> versionInfo1;
        std::unique_ptr<char> versionInfo2;
        std::unique_ptr<char> versionInfo3;

        // Nice grey color initially
        float m_color[4] = Color(xengine::GREY_COLOR);

        bool m_enableDebugLogs = Log::getInstance().isDebugLogEnabled();

    private:
        void drawDebugUI();
    };
}
