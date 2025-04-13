#pragma once

#include <window/events/Event.h>

namespace xengine {

    /**
     * A layer is very basic concept.
     * This is something which we can render on our screen.
     */
    class Layer : public EventConsumer
    {
    public:
        Layer() = default;
        ~Layer() override = default;

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onDraw() {}
        virtual void onDrawUI() {}
    };

}
