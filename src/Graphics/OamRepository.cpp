#include "OamRepository.h"
#include <nds.h>

OamRepository::OamRepository() {
    for (int i = 0; i < SPRITE_COUNT; i++) {
        availableOamIds.push(i);
    }
}

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