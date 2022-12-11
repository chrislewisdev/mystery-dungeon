#pragma once

#include <queue>
#include <map>

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
};