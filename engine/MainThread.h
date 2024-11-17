#pragma once

#include "Application.h"

/**
* Class which manages program execution on the main thread.
*/
class MainThread : public Lifecycle
{
public:
    MainThread() = default;
    ~MainThread() = default;

    void onCreate() override;
    void onDestroy() override;

    void loop(MainApplication* app);
private:
    bool m_ui_created = false;
};