#include "Map.h"

Map::Map(unique_ptr<u16[]>& contents) : virtualMap(move(contents)) {
    // virtualMap = make_unique<u16[]>(MAP_MEMORY_SIZE);
    mapVersion = 1;
}

void Map::load(const MemoryBlock& memory) {
    dmaCopy(memory.source, virtualMap.get(), memory.size);
    mapVersion++;
}

void Map::flushMap(u16* destination) {
    dmaCopy(virtualMap.get(), destination, sizeof(u16) * MAP_MEMORY_SIZE);
}

u16 Map::getMapVersion() {
    return mapVersion;
}

u16 Map::getTile(Vec2 location) {
    const int mapWidth = 32;
    Vec2 mapLocation = location * 2;
    return virtualMap[mapLocation.y * mapWidth + mapLocation.x];
}