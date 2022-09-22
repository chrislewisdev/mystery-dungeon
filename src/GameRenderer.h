#pragma once

#include "MemoryBlock.h"
#include "GameState.h"
#include "OamRepository.h"
#include "SpriteRepository.h"

class GameRenderer {
    private:
        int backgroundId = 0;
        u16 latestMapVersion = 0;
        OamRepository oamRepository;
        SpriteRepository spriteRepository;
    public:
        GameRenderer(OamState* oamMain);
        SpriteRepository& getSpriteRepository();
        void init(const MemoryBlock& bgPalette, const MemoryBlock& spritePalette, const MemoryBlock& tiles);
        void render(GameState& gameState);
};