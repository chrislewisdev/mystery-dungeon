#include "OamRepository.h"
#include <nds.h>

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
