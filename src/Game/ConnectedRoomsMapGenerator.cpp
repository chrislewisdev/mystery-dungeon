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

int sign(int x) {
    if (x == 0) return 0;
    return x > 0 ? 1 : -1;
}

void connectRooms(Rect2& source, Rect2& destination, u16* mapMemory, u16 mapWidth, MetaTileRepository& metaTileRepository) {
    Vec2 sourceMidpoint = source.midpoint();
    Vec2 destinationMidpoint = destination.midpoint();

    // Randomise whether moving across-then-down vs down-then-across.
    Vec2 anchor;
    if (rand() % 2 == 0) {
        anchor.x = sourceMidpoint.x;
        anchor.y = destinationMidpoint.y;
    } else {
        anchor.x = destinationMidpoint.x;
        anchor.y = sourceMidpoint.y;
    }

    for (int x = sourceMidpoint.x; x != destinationMidpoint.x; x += sign(destinationMidpoint.x - sourceMidpoint.x)) {
        mapMemory[anchor.y * mapWidth + x] = metaTileRepository.getFloorTileId();
    }
    for (int y = sourceMidpoint.y; y != destinationMidpoint.y; y += sign(destinationMidpoint.y - sourceMidpoint.y)) {
        mapMemory[y * mapWidth + anchor.x] = metaTileRepository.getFloorTileId();
    }
}

Rect2 generateRoom(int mapWidth, int mapHeight) {
    const int minimumRoomWidth = 5;
    const int minimumRoomHeight = 4;
    const int maximumRoomWidth = 10;
    const int maximumRoomHeight = 9;

    Vec2 location(rand() % (mapWidth - minimumRoomWidth), rand() % (mapHeight - minimumRoomHeight));
    Vec2 size(rand() % (maximumRoomWidth - minimumRoomWidth) + minimumRoomWidth, rand() % (maximumRoomHeight - minimumRoomHeight) + minimumRoomHeight);

    if (location.x + size.x > mapWidth) size.x = mapWidth - location.x;
    if (location.y + size.y > mapHeight) size.y = mapHeight - location.y;

    return Rect2(location, size);
}

Map ConnectedRoomsMapGenerator::generateMap() {
    const u16 width = 32, height = 24;
    unique_ptr<u16[]> contents = make_unique<u16[]>(width * height);

    const u16 ceilingTileId = metaTileRepository.getCeilingTileId();
    const u16 floorTileId = metaTileRepository.getFloorTileId();
    const u16 wallTileId = metaTileRepository.getWallTileId();

    // Fill memory with void tile
    dmaFillHalfWords(ceilingTileId, contents.get(), sizeof(u16) * width * height);

    Rect2 room = generateRoom(width, height);
    renderRoom(room, contents.get(), width, metaTileRepository);

    Rect2 room2 = generateRoom(width, height);
    renderRoom(room2, contents.get(), width, metaTileRepository);

    connectRooms(room2, room, contents.get(), width, metaTileRepository);

    return Map(metaTileRepository, width, height, contents);
}
