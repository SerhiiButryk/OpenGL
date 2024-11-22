#pragma once

#include "Internal.h"

#include <vector>

namespace xengine {

/**
* Class which manages program execution on the main thread.
*/
class MainThread : public Lifecycle
{
public:
    MainThread() = default;
    virtual ~MainThread() = default;

    void onCreate() override;
    void onDestroy() override;

    void addThreadObserver(MainThreadObserver* observer);
    void removeThreadObserver(MainThreadObserver* observer);

    void loop(InternalApplication* app);
private:
    std::vector<MainThreadObserver*> m_observers;
};

}