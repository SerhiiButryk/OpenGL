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

        // Objects are not deleted by this class
        // Memory is managed by a caller
        void addThreadObserver(MainThreadObserver* observer);
        void removeThreadObserver(MainThreadObserver* observer);

        void loop(InternalApplication* app);

        void quit() { m_stop = true; }

#ifdef UNIT_TESTS
        bool checkEmptyListForTest() { return m_observers.empty(); }
#endif

    private:
        std::vector<MainThreadObserver*> m_observers;
        bool m_stop = false;
    };

}