#include "Map.h"

Map::Map(MetaTileRepository& metaTileRepository, u16 width, u16 height, unique_ptr<u16[]>& contents)
: metaTileRepository(metaTileRepository), metamapWidth(width), metamapHeight(height), metamap(move(contents)) {
    virtualMap = make_unique<u16[]>(VIRTUAL_MAP_WIDTH * VIRTUAL_MAP_HEIGHT);
    renderMetamap(Vec2());
}

void Map::flushMap(u16* destination) {
    dmaCopy(virtualMap.get(), destination, sizeof(u16) * VIRTUAL_MAP_WIDTH * VIRTUAL_MAP_HEIGHT);
}

u16 Map::getMapVersion() {
    return mapVersion;
}

MetaTile Map::getTile(Vec2 location) {
    u16 metaTileId = metamap[location.y * metamapWidth + location.x];
    return metaTileRepository.get(metaTileId);
}

void renderTile(u16* virtualMap, Vec2 location, u16 tile) {
    virtualMap[location.y * VIRTUAL_MAP_WIDTH + location.x] = tile;
}

void Map::renderMetamap(Vec2 cameraLocation) {
    for (int x = 0; x < SCREEN_TILE_WIDTH; x++) {
        for (int y = 0; y < SCREEN_TILE_HEIGHT; y++) {
            Vec2 metamapAddress = cameraLocation + Vec2(x, y);
            u16 metaTileId = isInBounds(metamapAddress)
                ? metamap[metamapAddress.y * metamapWidth + metamapAddress.x]
                : metaTileRepository.getCeilingTileId();
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
    mapVersion++;
}

bool Map::isInBounds(Vec2 metamapAddress) {
    if (metamapAddress.x < 0) return false;
    if (metamapAddress.y < 0) return false;
    if (metamapAddress.x >= metamapWidth) return false;
    if (metamapAddress.y >= metamapHeight) return false;

    return true;
}
