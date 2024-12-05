#pragma once
#include <unordered_map>

namespace test {

    /**
    * Simple memory tracker for test
    */
    class MemoryTracker {
    public:

        struct Allocation {
        };

        std::unordered_map<void*, Allocation> deallocations;

        bool checkIfDeallocated(void* obj) const;
        void addToList(void* obj);
        void clear();
        void setTrack(bool val);

        static bool track;
    };

}


