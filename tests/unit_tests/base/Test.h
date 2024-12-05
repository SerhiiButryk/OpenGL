#pragma once

#include "MemoryTracker.h"

namespace test {

    class Test 
    {
    public:
        Test() = default;
        virtual ~Test() = default;

        virtual int run() const = 0;
        virtual const char* name() const = 0;

        void setMemoryTracker(MemoryTracker* memoryTracker) { m_memoryTracker = memoryTracker; }
    protected:
        MemoryTracker* m_memoryTracker = nullptr;
    };

}
