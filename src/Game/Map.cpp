#include "Map.h"

Map::Map(MetaTileRepository& metaTileRepository, unique_ptr<u16[]>& contents)
: metaTileRepository(metaTileRepository), metamap(move(contents)) {
    virtualMap = make_unique<u16[]>(VIRTUAL_MAP_WIDTH * VIRTUAL_MAP_HEIGHT);
    renderMetamap(16, 12);
}

void Map::flushMap(u16* destination) {
    dmaCopy(virtualMap.get(), destination, sizeof(u16) * VIRTUAL_MAP_WIDTH * VIRTUAL_MAP_HEIGHT);
}

u16 Map::getMapVersion() {
    return mapVersion;
}

MetaTile Map::getTile(Vec2 location) {
    // TODO: This wil need to come from the map generator
    const int mapWidth = 16;
    u16 metaTileId = metamap[location.y * mapWidth + location.x];
    return metaTileRepository.get(metaTileId);
}

void renderTile(u16* virtualMap, Vec2 location, u16 tile) {
    virtualMap[location.y * VIRTUAL_MAP_WIDTH + location.x] = tile;
}

void Map::renderMetamap(int width, int height) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            u16 metaTileId = metamap[y * width + x];
            MetaTile metaTile = metaTileRepository.get(metaTileId);
            Vec2 virtualMapAddress(x * 2, y * 2);
            Vec2 right(1, 0);
            Vec2 down(0, 1);
            renderTile(virtualMap.get(), virtualMapAddress, metaTile.getTopLeftTile());
            renderTile(virtualMap.get(), virtualMapAddress + right, metaTile.getTopRightTile());
            renderTile(virtualMap.get(), virtualMapAddress + down, metaTile.getBottomLeftTile());
            renderTile(virtualMap.get(), virtualMapAddress + right + down, metaTile.getBottomRightTile());
        }
    }
}
