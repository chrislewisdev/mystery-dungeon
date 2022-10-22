#pragma once

#include <nds.h>
#include <memory>
#include "Core/MemoryBlock.h"
#include "Core/Vec2.h"
#include "Core/MetaTileRepository.h"

using namespace std;

#define VIRTUAL_MAP_WIDTH   32
#define VIRTUAL_MAP_HEIGHT  24

class Map {
    private:
        u16 mapVersion = 1;
        MetaTileRepository& metaTileRepository;
        unique_ptr<u16[]> metamap;
        unique_ptr<u16[]> virtualMap;
    public:
        Map(MetaTileRepository& metaTileRepository, unique_ptr<u16[]>& contents);
        void flushMap(u16* destination);
        u16 getMapVersion();
        // Gets the value of the tile at x/y USING GAME CO-ORDINATES. 
        u16 getTile(Vec2 location);
        void renderMetamap(int width, int height);
};