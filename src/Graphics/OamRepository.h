#pragma once

#include <queue>
#include <map>

class OamRepository {
    private:
        std::queue<int> availableOamIds;
        std::map<int, int> oamAllocations;
    public:
        OamRepository();
        int getOrAllocateOamId(int characterId);
};