#include "Game/RoomMapGenerator.h"
#include <memory>

using namespace std;

RoomMapGenerator::RoomMapGenerator(MetaTileRepository& metaTileRepository) : metaTileRepository(metaTileRepository) {}

Map RoomMapGenerator::generateMap() {
    const u16 width = 32, height = 24;
    unique_ptr<u16[]> contents = make_unique<u16[]>(width * height);

    const u16 ceilingTileId = metaTileRepository.getCeilingTileId();
    const u16 floorTileId = metaTileRepository.getFloorTileId();
    const u16 wallTileId = metaTileRepository.getWallTileId();

    // Fill memory with floor tile
    dmaFillHalfWords(floorTileId, contents.get(), sizeof(u16) * width * height);

    u16* rawMap = contents.get();
    // Generate walls - top and bottom wall
    for (u16 x = 0; x < width; x++) {
        rawMap[x] = ceilingTileId;
        rawMap[width + x] = wallTileId;
        rawMap[(height - 1) * width + x] = ceilingTileId;
    }
    // Left and right walls
    for (u16 y = 0; y < height; y++) {
        rawMap[y * width] = ceilingTileId;
        rawMap[y * width + (width - 1)] = ceilingTileId;
    }
    //Insert some features to break up the floor
    for (u16 x = 8; x < width; x += 8) {
        rawMap[width*2 + x] = ceilingTileId;
    }

    return Map(metaTileRepository, width, height, contents);
}