#include "OamRepository.h"
#include <nds.h>
#include "Core/Linq.h"

using namespace std;

OamRepository::OamRepository() {
    for (int i = 0; i < SPRITE_COUNT; i++) {
        availableOamIds.push(i);
    }
}

int OamRepository::getAvailableIdCount() { return availableOamIds.size(); }

int OamRepository::getOrAllocateOamId(int characterId) {
    if (oamAllocations.find(characterId) != oamAllocations.end()) {
        return oamAllocations.at(characterId);
    } else {
        // TODO: Handle no available ids
        int oamId = availableOamIds.front();
        availableOamIds.pop();
        oamAllocations[characterId] = oamId;
        return oamId;
    }
}

int OamRepository::getOamId(int characterId) {
    auto item = oamAllocations.find(characterId);

    if (item == oamAllocations.end()) return -1;

    return item->second;
}

void OamRepository::freeOamId(int characterId) {
    auto item = oamAllocations.find(characterId);
    
    if (item == oamAllocations.end()) return;

    availableOamIds.push(item->second);
    oamAllocations.erase(item);
}

void OamRepository::freeUnusedAllocations(vector<int> usedCharacterIds) {
    for (auto it = oamAllocations.begin(); it != oamAllocations.end(); it++) {
        if (!contains(usedCharacterIds, it->first)) {
            availableOamIds.push(it->second);
            it = oamAllocations.erase(it);
        }
    }
}
