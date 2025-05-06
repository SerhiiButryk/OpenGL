#include "Registry.h"

#include <common/Log.h>
#include "Assert.h"

namespace test {

    void Registry::add(Test* test) {
        m_tests.insert(std::pair(test->name(), test));
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
        ASSERT_LOG(false, "Registry::runTest() test wasn't found");
    }

    Registry& Registry::instance() {
        static Registry registry;
        return registry;
    }
}
