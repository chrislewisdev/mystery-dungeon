#pragma once

#include <nds.h>
#include "MemoryBlock.h"

class Map {
    private:
        u16 mapVersion = 0;
        u16 virtualMap[1024];
    public:
        void load(const MemoryBlock& memory);
        void flushMap(u16* destination);
        u16 getMapVersion();
};