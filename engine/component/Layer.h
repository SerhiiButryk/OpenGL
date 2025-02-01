#pragma once

#include <app/Lifecycle.h>
#include <window/events/Event.h>

namespace xengine {

    /**
     * A layer is very basic concept.
     * This is something which we can render at once.
     */
    class Layer : public Lifecycle, public EventConsumer
    {
    public:
        Layer() = default;
        ~Layer() override = default;

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onDraw() {}
    };

}
