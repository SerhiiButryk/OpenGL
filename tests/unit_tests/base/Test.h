#pragma once

#include "MemoryTracker.h"

namespace test {

    class Test 
    {
    public:
        // Test() {
        //     // Register this test
        //     auto* name = name();
        //     Registry::instance().add(this, name);
        // };

        Test() = default;

        virtual ~Test() = default;

        virtual int run() const {}
        virtual const char* name() const { return ""; }

        void setMemoryTracker(MemoryTracker* memoryTracker) { m_memoryTracker = memoryTracker; }
    protected:
        MemoryTracker* m_memoryTracker = nullptr;
    };

}
