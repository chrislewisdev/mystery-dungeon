#include "Map.h"

using namespace std;

Map::Map(
    MetaTileRepository& metaTileRepository,
    Metamap metamap,
    Vec2 startingLocation,
    vector<Rect2> rooms
) : metaTileRepository(metaTileRepository),
    metamap(metamap),
    startingLocation(startingLocation),
    rooms(rooms)
{
    virtualMap = make_unique<u16[]>(VIRTUAL_MAP_WIDTH * VIRTUAL_MAP_HEIGHT);
    renderMetamap(Vec2());
}

u16 Map::getMapVersion() { return mapVersion; }
Vec2 Map::getStartingLocation() { return startingLocation; }
vector<Rect2>& Map::getRooms() { return rooms; }

void Map::flushMap(u16* destination) {
    dmaCopy(virtualMap.get(), destination, sizeof(u16) * VIRTUAL_MAP_WIDTH * VIRTUAL_MAP_HEIGHT);
}

MetaTile Map::getTile(Vec2 location) {
    u16 metaTileId = metamap.getTile(location.x, location.y);
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
                ? metamap.getTile(metamapAddress.x, metamapAddress.y)
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

// Might belong in Metamap more...
bool Map::isInBounds(Vec2 metamapAddress) {
    if (metamapAddress.x < 0) return false;
    if (metamapAddress.y < 0) return false;
    if (metamapAddress.x >= metamap.getWidth()) return false;
    if (metamapAddress.y >= metamap.getHeight()) return false;

    return true;
}

Map& Map::operator=(Map&& other) {
    mapVersion++;
    startingLocation = other.startingLocation;
    metamap = other.metamap;

    return *this;
}
