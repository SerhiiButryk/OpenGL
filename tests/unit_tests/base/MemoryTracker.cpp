#include "MemoryTracker.h"

namespace test {

    bool MemoryTracker::checkIfDeallocated(void* obj) const {
        if (auto elem = deallocations.find(obj); elem != deallocations.end()) {
            return true;
        }
        return false;
    }

    void MemoryTracker::addToList(void* obj) {
        if (track) {
            deallocations[obj] = {};
        }
    }

    void MemoryTracker::clear() {
        deallocations.clear();
    }

    void MemoryTracker::setTrack(bool val) {
        track = val;
    }

    bool MemoryTracker::track = false;
}