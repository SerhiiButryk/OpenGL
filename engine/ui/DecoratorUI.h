#pragma once

#include <app/Application.h>

namespace xengine {

    /**
    * Application UI component.
    * This is a first UI layer of our application.
    * It could add additional UI components in the future.
    */
    class DecoratorUI : public Layer
    {
    public:
        explicit DecoratorUI(void*);
        ~DecoratorUI() override;

        void onAttach() override;

        void onDetach() override;

        void onDraw() override;

    private:
        // Ref to window implementation
        void* m_nativeWindow;
        bool m_isAttached = false;
    };
}
