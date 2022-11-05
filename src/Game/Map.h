#pragma once

#include <nds.h>
#include <memory>
#include "Core/MemoryBlock.h"
#include "Core/Vec2.h"
#include "Core/MetaTileRepository.h"

using namespace std;

#define SCREEN_TILE_WIDTH   16
#define SCREEN_TILE_HEIGHT  12
#define VIRTUAL_MAP_WIDTH   32
#define VIRTUAL_MAP_HEIGHT  24

class Map {
    private:
        u16 mapVersion = 0;
        MetaTileRepository& metaTileRepository;
        u16 metamapWidth, metamapHeight;
        unique_ptr<u16[]> metamap;
        unique_ptr<u16[]> virtualMap;
        
        bool isInBounds(Vec2 metamapAddress);
    public:
        Map(MetaTileRepository& metaTileRepository, u16 width, u16 height, unique_ptr<u16[]>& contents);
        void flushMap(u16* destination);
        u16 getMapVersion();
        // Gets the tile at x/y USING GAME CO-ORDINATES. 
        MetaTile getTile(Vec2 location);
        void renderMetamap(Vec2 cameraLocation);
};