#include <common/Log.h>

#include <BasicTest.h>

#include "BasicScenerioTests.h"
#include "MemoryTracker.h"
#include "Registry.h"

static test::MemoryTracker memoryTracker;

void *operator new(std::size_t sz) {
    if (sz == 0)
        ++sz; // avoid std::malloc(0) which may return nullptr on success

    if (void *ptr = std::malloc(sz))
        return ptr;

    throw std::bad_alloc{}; // required by [new.delete.single]/3
}

void operator delete(void *ptr) noexcept {
    std::free(ptr);

    memoryTracker.addToList(ptr);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        LOG_ERROR("Not enough arguments");
        return 1;
    }

    using namespace test;

    // Our tests
    BasicTest basic_test;
    BasicScenerioTests basic_scenerio_tests;

    Registry::instance().add(&basic_test);
    Registry::instance().add(&basic_scenerio_tests);

    int result = Registry::instance()
            .runTest(argv[1] /* Current test name */, memoryTracker);;

    return result;
}
