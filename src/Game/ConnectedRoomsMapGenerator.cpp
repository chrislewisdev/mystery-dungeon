#include "Game/ConnectedRoomsMapGenerator.h"
#include <memory>
#include <vector>
#include "Core/Rect2.h"
#include "Game/Metamap.h"

using namespace std;

ConnectedRoomsMapGenerator::ConnectedRoomsMapGenerator(MetaTileRepository& metaTileRepository) : metaTileRepository(metaTileRepository) {}

void renderRoom(Rect2& room, Metamap& metamap, MetaTileRepository& metaTileRepository) {
    metamap.fill(room.location.x, room.location.y, room.size.x, metaTileRepository.getWallTileId());
    for (u16 y = room.location.y + 1; y < room.location.y + room.size.y; y++) {
        metamap.fill(room.location.x, y, room.size.x, metaTileRepository.getFloorTileId());
    }
}

int sign(int x) {
    if (x == 0) return 0;
    return x > 0 ? 1 : -1;
}

void connectRooms(Rect2& source, Rect2& destination, Metamap& metamap, MetaTileRepository& metaTileRepository) {
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
        metamap.setTile(x, anchor.y, metaTileRepository.getFloorTileId());

        if (metamap.getTile(x, anchor.y - 1) == metaTileRepository.getCeilingTileId())
            metamap.setTile(x, anchor.y - 1, metaTileRepository.getWallTileId());
    }
    for (int y = sourceMidpoint.y; y != destinationMidpoint.y; y += sign(destinationMidpoint.y - sourceMidpoint.y)) {
        metamap.setTile(anchor.x, y, metaTileRepository.getFloorTileId());
    }
}

Rect2 generateRoom(int mapWidth, int mapHeight) {
    const int minimumRoomWidth = 8;
    const int minimumRoomHeight = 7;
    const int maximumRoomWidth = 16;
    const int maximumRoomHeight = 14;

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
    int roomCount = rand() % 3 + 4;
    const u16 width = roomCount * 7, height = roomCount * 7;
    Metamap metamap(width, height);

    // Fill memory with void tile
    metamap.fill(metaTileRepository.getCeilingTileId());

    vector<Rect2> rooms;
    for (int i = 0; i < roomCount; i++) {
        Rect2 room = generateRoom(width, height);
        renderRoom(room, metamap, metaTileRepository);
        rooms.push_back(room);
    }

    // Connect all rooms together - should probably be more selective
    for (u8 i = 0; i < rooms.size() - 1; i++) {
        for (u8 j = i + 1; j < rooms.size(); j++) {
            connectRooms(rooms[i], rooms[j], metamap, metaTileRepository);
        }
    }

    // Pop a stair in the first room (for testing)
    Vec2 stairsLocation = generateStartingLocation(rooms[0]);
    metamap.setTile(stairsLocation.x, stairsLocation.y, metaTileRepository.getStairsTileId());

    return Map(metaTileRepository, metamap, generateStartingLocation(rooms[0]));
}
