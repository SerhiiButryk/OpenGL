#pragma once

#include "internal/Lifecycle.h"
#include "internal/InternalApplication.h"
#include "internal/MainThreadObserver.h"

#include <vector>

namespace xengine {

    /**
    * Class which manages program execution on the main thread.
    */
    class MainThread : public Lifecycle
    {
    public:
        MainThread() = default;
        ~MainThread() override = default;

        void onCreate() override;
        void onDestroy() override;

        void addThreadObserver(MainThreadObserver* observer);
        void removeThreadObserver(MainThreadObserver* observer);

        void loop(InternalApplication* app);

#ifdef UNIT_TESTS
        void* getObserverForTest() { return m_observers[0]; }
        bool checkEmptyListForTest() { return m_observers.empty(); }
#endif

    private:
        std::vector<MainThreadObserver*> m_observers;
    };

}