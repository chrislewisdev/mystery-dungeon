#include "Map.h"

Map::Map() {
    virtualMap = new u16[MAP_MEMORY_SIZE];
}

void Map::load(const MemoryBlock& memory) {
    dmaCopy(memory.source, virtualMap, memory.size);
    mapVersion++;
}

void Map::flushMap(u16* destination) {
    dmaCopy(virtualMap, destination, sizeof(u16) * MAP_MEMORY_SIZE);
}

u16 Map::getMapVersion() {
    return mapVersion;
}

u16 Map::getTile(Vec2 location) {
    const int mapWidth = 32;
    Vec2 mapLocation = location * 2;
    return virtualMap[mapLocation.y * mapWidth + mapLocation.x];
}