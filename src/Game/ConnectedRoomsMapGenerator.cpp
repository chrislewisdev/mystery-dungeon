#include "Game/ConnectedRoomsMapGenerator.h"
#include <memory>
#include "Core/Rect2.h"

using namespace std;

ConnectedRoomsMapGenerator::ConnectedRoomsMapGenerator(MetaTileRepository& metaTileRepository) : metaTileRepository(metaTileRepository) {}

void renderRoom(Rect2& room, u16* mapMemory, u16 mapWidth, MetaTileRepository& metaTileRepository) {
    dmaFillHalfWords(metaTileRepository.getWallTileId(), mapMemory + room.location.y * mapWidth + room.location.x, sizeof(u16) * room.size.x);
    for (u16 y = room.location.y + 1; y < room.location.y + room.size.y; y++) {
        u16* address = mapMemory + (y * mapWidth) + room.location.x;
        dmaFillHalfWords(metaTileRepository.getFloorTileId(), address, sizeof(u16) * room.size.x);
    }
}

// TODO: Make this actually work properly...
void connectRooms(Rect2& source, Rect2& destination, u16* mapMemory, u16 mapWidth, MetaTileRepository& metaTileRepository) {
    int direction = source.left() > destination.left() ? -1 : 1;

    Vec2 pathPoint = source.location + Vec2(-1, 1);

    while (pathPoint.x <= destination.left() || pathPoint.x >= destination.right()) {
        pathPoint.x += direction;
    }

    int yDirection = pathPoint.y < destination.top() ? 1 : -1;
    while (pathPoint.y <= destination.top() || pathPoint.y >= destination.bottom()) {
        mapMemory[pathPoint.y * mapWidth + pathPoint.x] = metaTileRepository.getFloorTileId();
        pathPoint.y += yDirection;
    }
}

Map ConnectedRoomsMapGenerator::generateMap() {
    const u16 width = 32, height = 24;
    unique_ptr<u16[]> contents = make_unique<u16[]>(width * height);

    const u16 ceilingTileId = metaTileRepository.getCeilingTileId();
    const u16 floorTileId = metaTileRepository.getFloorTileId();
    const u16 wallTileId = metaTileRepository.getWallTileId();

    // Fill memory with void tile
    dmaFillHalfWords(ceilingTileId, contents.get(), sizeof(u16) * width * height);

    Rect2 room(Vec2(3, 2), Vec2(8, 5));
    renderRoom(room, contents.get(), width, metaTileRepository);

    Rect2 room2(Vec2(10, 9), Vec2(3, 3));
    renderRoom(room2, contents.get(), width, metaTileRepository);

    connectRooms(room2, room, contents.get(), width, metaTileRepository);

    return Map(metaTileRepository, width, height, contents);
}
