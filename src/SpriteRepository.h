#pragma once

#include <nds.h>
#include <map>
#include "MemoryBlock.h"

class SpriteRepository {
    private:
        OamState* oam;
        std::map<int, u16*> sprites;
    public:
        SpriteRepository(OamState* oam);
        void loadSprite(int typeId, MemoryBlock gfx);
        u16* getSprite(int typeId);
};