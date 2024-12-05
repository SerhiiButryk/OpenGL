#include "Registry.h"

#include <common/Log.h>

namespace test {

    void Registry::add(Test* test, const std::string& name) {
        m_tests.insert(std::pair(name, test));
    }

    void Registry::remove(const std::string& name) {
        m_tests.erase(name);
    }

    int Registry::runTest(const std::string& name, MemoryTracker& memoryTracker) const {
        if (auto elem = m_tests.find(name); elem != m_tests.end()) {
            // Run selected test
            elem->second->setMemoryTracker(&memoryTracker);
            return elem->second->run();
        }
        logError("Registry::runTest() test wasn't found");
        // Failure
        return 1;
    }

}
