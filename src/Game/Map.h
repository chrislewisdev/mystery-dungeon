#pragma once

#include <nds.h>
#include <memory>
#include "Core/MemoryBlock.h"
#include "Core/Vec2.h"
#include "Core/MetaTileRepository.h"
#include "Game/Metamap.h"

#define SCREEN_TILE_WIDTH   16
#define SCREEN_TILE_HEIGHT  12
#define VIRTUAL_MAP_WIDTH   32
#define VIRTUAL_MAP_HEIGHT  24

class Map {
    private:
        u16 mapVersion = 0;
        MetaTileRepository& metaTileRepository;
        Metamap metamap;
        std::unique_ptr<u16[]> virtualMap;
        Vec2 startingLocation;
        
        bool isInBounds(Vec2 metamapAddress);
    public:
        Map(MetaTileRepository& metaTileRepository, Metamap metamap, Vec2 startingLocation);
        u16 getMapVersion();
        Vec2 getStartingLocation();
        void flushMap(u16* destination);
        // Gets the tile at x/y USING GAME CO-ORDINATES. 
        MetaTile getTile(Vec2 location);
        void renderMetamap(Vec2 cameraLocation);
};