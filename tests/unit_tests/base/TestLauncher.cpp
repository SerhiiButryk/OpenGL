#include <common/Log.h>
#include <unit_tests/MemoryLeakTest.h>

#include "MemoryTracker.h"
#include "Registry.h"

static test::MemoryTracker memoryTracker;

void* operator new(std::size_t sz)
{
    if (sz == 0)
        ++sz; // avoid std::malloc(0) which may return nullptr on success

    if (void *ptr = std::malloc(sz))
        return ptr;

    throw std::bad_alloc{}; // required by [new.delete.single]/3
}

void operator delete(void* ptr) noexcept
{
    std::free(ptr);

    memoryTracker.addToList(ptr);
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        logError("Not enough arguments");
        return 1;
    }

    using namespace test;

    MemoryLeakTest memory_leak_test;

    Registry registry;
    registry.add(&memory_leak_test, memory_leak_test.name());

    auto* testName = argv[1];
    int result = registry.runTest(testName, memoryTracker);;

    return result;
}
