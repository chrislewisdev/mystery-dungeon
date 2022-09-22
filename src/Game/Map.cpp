#include "Map.h"

void Map::load(const MemoryBlock& memory) {
    dmaCopy(memory.source, virtualMap, memory.size);
    mapVersion++;
}

void Map::flushMap(u16* destination) {
    dmaCopy(virtualMap, destination, sizeof(virtualMap));
}

u16 Map::getMapVersion() {
    return mapVersion;
}