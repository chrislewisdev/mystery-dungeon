#pragma once

#include <nds.h>
#include "Core/MemoryBlock.h"
#include "Core/Vec2.h"

class Map {
    private:
        u16 mapVersion = 0;
        u16 virtualMap[1024];
    public:
        void load(const MemoryBlock& memory);
        void flushMap(u16* destination);
        u16 getMapVersion();
        // Gets the value of the tile at x/y USING GAME CO-ORDINATES. 
        u16 getTile(int x, int y);
};