#pragma once

#include <string>
#include <unordered_map>

#include "MemoryTracker.h"
#include "Test.h"

namespace test {

    class Registry 
    {
    public:
        void add(Test* test, const std::string& name);
        void remove(const std::string& name);

        int runTest(const std::string& name, MemoryTracker& memoryTracker) const;

    private:
        std::unordered_map<std::string, Test*> m_tests;
    };

}
