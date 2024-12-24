#pragma once

namespace xengine {

    class EventListener
    {
    public:
        EventListener() = default;
        virtual ~EventListener() = default;

        virtual bool onEvent(const Event& event) { return false; }
    };
}
