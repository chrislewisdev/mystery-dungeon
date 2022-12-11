#pragma once

#include <queue>
#include <map>
#include <vector>

// Not used ATM in favour of just cycling through IDs on every render. Has some bugs.
class OamRepository {
    private:
        std::queue<int> availableOamIds;
        std::map<int, int> oamAllocations;
    public:
        OamRepository();
        int getAvailableIdCount();
        int getOrAllocateOamId(int characterId);
        int getOamId(int characterId);
        void freeOamId(int characterId);
        void freeUnusedAllocations(std::vector<int> usedCharacterIds);
};