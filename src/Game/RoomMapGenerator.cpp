#include "Game/RoomMapGenerator.h"
#include <memory>
#include "Game/Metamap.h"

using namespace std;

RoomMapGenerator::RoomMapGenerator(MetaTileRepository& metaTileRepository) : metaTileRepository(metaTileRepository) {}

Map RoomMapGenerator::generateMap() {
    const u16 width = 32, height = 24;
    Metamap metamap(width, height);

    const u16 ceilingTileId = metaTileRepository.getCeilingTileId();
    const u16 floorTileId = metaTileRepository.getFloorTileId();
    const u16 wallTileId = metaTileRepository.getWallTileId();

    // Fill memory with floor tile
    metamap.fill(floorTileId);

    // Generate walls - top and bottom wall
    for (u16 x = 0; x < width; x++) {
        metamap.setTile(x, 0, ceilingTileId);
        metamap.setTile(x, 1, wallTileId);
        metamap.setTile(x, height - 1, ceilingTileId);
    }
    // Left and right walls
    for (u16 y = 0; y < height; y++) {
        metamap.setTile(0, y, ceilingTileId);
        metamap.setTile(width - 1, y, ceilingTileId);
    }
    //Insert some features to break up the floor
    for (u16 x = 8; x < width; x += 8) {
        metamap.setTile(x, 2, ceilingTileId);
    }

    return Map(metaTileRepository, metamap, Vec2(5, 5));
}