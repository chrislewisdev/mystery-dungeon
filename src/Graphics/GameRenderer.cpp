#include "GameRenderer.h"
#include <nds.h>
#include <stdio.h>

#define TILE_SIZE 16

GameRenderer::GameRenderer(OamState* oamMain) : spriteRepository(oamMain) {}

SpriteRepository& GameRenderer::getSpriteRepository() { return spriteRepository; }

void GameRenderer::init(const MemoryBlock& bgPalette, const MemoryBlock& spritePalette, const MemoryBlock& tiles){
    lcdMainOnBottom();
    
    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankB(VRAM_B_MAIN_SPRITE);

    oamInit(&oamMain, SpriteMapping_1D_32, false);

    backgroundId = bgInit(0, BgType_Text4bpp, BgSize_T_256x256, 0, 1);

    dmaCopy(bgPalette.source, BG_PALETTE, bgPalette.size);
    dmaCopy(spritePalette.source, SPRITE_PALETTE, spritePalette.size);
    dmaCopy(tiles.source, bgGetGfxPtr(backgroundId), tiles.size);
}

void GameRenderer::render(GameState& gameState) {
    // Update map data if changed
    Map& map = gameState.getMap();
    if (map.getMapVersion() > latestMapVersion) {
        map.flushMap(bgGetMapPtr(backgroundId));
        latestMapVersion = map.getMapVersion();
    }

    for (Character& character : gameState.getCharacters()) {
        // TODO: camera culling
        int oamId = oamRepository.getOrAllocateOamId(character.getId());
        iprintf("%d\n", oamId);
        u16* sprite = spriteRepository.getSprite(character.getType());
        Vec2 location = character.getLocation();
        oamSet(&oamMain, oamId,
            location.x * TILE_SIZE, location.y * TILE_SIZE,
            0, 0, SpriteSize_16x16, SpriteColorFormat_16Color, sprite, 0, false, false, false, false, false);
    }
    // TODO: Release oam ids for things no longer displayed

    // Render game world (bottom screen?)
    // Render HUD (top screen?)

    oamUpdate(&oamMain);
}