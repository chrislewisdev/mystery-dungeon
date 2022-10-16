#pragma once

#include <nds.h>
#include "Core/MemoryBlock.h"
#include "Core/Vec2.h"

#define MAP_MEMORY_SIZE 1024

class Map {
    private:
        u16 mapVersion = 0;
        u16* virtualMap;
    public:
        Map();
        void load(const MemoryBlock& memory);
        void flushMap(u16* destination);
        u16 getMapVersion();
        // Gets the value of the tile at x/y USING GAME CO-ORDINATES. 
        u16 getTile(Vec2 location);
};