#include "Game/RoomMapGenerator.h"
#include <memory>

using namespace std;

Map RoomMapGenerator::generateMap() {
    const int width = 32, height = 32;
    unique_ptr<u16[]> contents = make_unique<u16[]>(width * height);

    // Fill memory with floor tile
    dmaFillHalfWords(5, contents.get(), sizeof(u16) * width * height);

    u16* rawMap = contents.get();
    // Generate walls - top and bottom wall
    for (int x = 0; x < width; x++) {
        rawMap[x] = 0;
        rawMap[(height - 1) * width + x] = 0;
    }
    // Left and right walls
    for (int y = 0; y < height; y++) {
        rawMap[y * width] = 0;
        rawMap[y * width + (width - 1)] = 0;
    }

    return Map(contents);
}