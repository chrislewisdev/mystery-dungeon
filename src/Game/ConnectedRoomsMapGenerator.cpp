#include "Game/ConnectedRoomsMapGenerator.h"
#include <memory>
#include <vector>
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

        int a = (anchor.y - 1) * mapWidth + x;
        if (mapMemory[a] == metaTileRepository.getCeilingTileId())
            mapMemory[a] = metaTileRepository.getWallTileId();
    }
    for (int y = sourceMidpoint.y; y != destinationMidpoint.y; y += sign(destinationMidpoint.y - sourceMidpoint.y)) {
        mapMemory[y * mapWidth + anchor.x] = metaTileRepository.getFloorTileId();
    }
}

Rect2 generateRoom(int mapWidth, int mapHeight) {
    const int minimumRoomWidth = 6;
    const int minimumRoomHeight = 4;
    const int maximumRoomWidth = 10;
    const int maximumRoomHeight = 9;

    Vec2 location(rand() % (mapWidth - minimumRoomWidth), rand() % (mapHeight - minimumRoomHeight));
    Vec2 size(rand() % (maximumRoomWidth - minimumRoomWidth) + minimumRoomWidth, rand() % (maximumRoomHeight - minimumRoomHeight) + minimumRoomHeight);

    if (location.x + size.x > mapWidth) size.x = mapWidth - location.x;
    if (location.y + size.y > mapHeight) size.y = mapHeight - location.y;

    return Rect2(location, size);
}

Vec2 generateStartingLocation(Rect2 room) {
    return room.location + Vec2(rand() % room.size.x, rand() % (room.size.y - 1) + 1);
}

Map ConnectedRoomsMapGenerator::generateMap() {
    const u16 width = 32, height = 24;
    unique_ptr<u16[]> contents = make_unique<u16[]>(width * height);

    const u16 ceilingTileId = metaTileRepository.getCeilingTileId();

    // Fill memory with void tile
    dmaFillHalfWords(ceilingTileId, contents.get(), sizeof(u16) * width * height);

    int roomCount = rand() % 3 + 4;
    vector<Rect2> rooms;
    for (int i = 0; i < roomCount; i++) {
        Rect2 room = generateRoom(width, height);
        renderRoom(room, contents.get(), width, metaTileRepository);
        rooms.push_back(room);
    }

    // Connect all rooms together - should probably be more selective
    for (int i = 0; i < rooms.size() - 1; i++) {
        for (int j = i + 1; j < rooms.size(); j++) {
            connectRooms(rooms[i], rooms[j], contents.get(), width, metaTileRepository);
        }
    }

    return Map(metaTileRepository, width, height, contents, generateStartingLocation(rooms[0]));
}
