#pragma once

namespace xengine {

    /**
    * Lifecycle component interface
    */
    class Lifecycle {
    public:

        Lifecycle() = default;
        virtual ~Lifecycle() = default;

        virtual void onCreate() {}
        virtual void onDestroy() {}
    };
}