#pragma once

namespace xengine {

    static inline int EVENT_WINDOW_CLOSE = 1;

    class Event {
    public:
        Event() = default;
        virtual ~Event() = default;

        int type = 0;
    };

    class EventConsumer {
    public:
        EventConsumer() = default;
        virtual ~EventConsumer() = default;

        virtual bool onEvent(const Event& event) { return false; }
    };

    class EventDispatcher {
    public:
        EventDispatcher() = default;
        virtual ~EventDispatcher() = default;

        virtual void dispatch(const Event& event) {}
    };
}
