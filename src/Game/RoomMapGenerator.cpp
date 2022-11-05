#include "Game/RoomMapGenerator.h"
#include <memory>

using namespace std;

RoomMapGenerator::RoomMapGenerator(MetaTileRepository& metaTileRepository) : metaTileRepository(metaTileRepository) {}

Map RoomMapGenerator::generateMap() {
    const int width = 16, height = 12;
    unique_ptr<u16[]> contents = make_unique<u16[]>(width * height);

    const u16 ceilingTileId = metaTileRepository.getCeilingTileId();
    const u16 floorTileId = metaTileRepository.getFloorTileId();
    const u16 wallTileId = metaTileRepository.getWallTileId();

    // Fill memory with floor tile
    dmaFillHalfWords(floorTileId, contents.get(), sizeof(u16) * width * height);

    u16* rawMap = contents.get();
    // Generate walls - top and bottom wall
    for (int x = 0; x < width; x++) {
        rawMap[x] = ceilingTileId;
        rawMap[width + x] = wallTileId;
        rawMap[(height - 1) * width + x] = ceilingTileId;
    }
    // Left and right walls
    for (int y = 0; y < height; y++) {
        rawMap[y * width] = ceilingTileId;
        rawMap[y * width + (width - 1)] = ceilingTileId;
    }

    return Map(metaTileRepository, contents);
}