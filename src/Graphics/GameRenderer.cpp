#include "GameRenderer.h"
#include <nds.h>
#include <stdio.h>
#include "Core/Const.h"
#include "Core/Linq.h"

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
    if (map.getMapVersion() != latestMapVersion) {
        map.flushMap(bgGetMapPtr(backgroundId));
        latestMapVersion = map.getMapVersion();
    }

    auto isInView = [&gameState](const Character& character) {
        Vec2 location = character.getLocation() - gameState.getCameraLocation();
        return location.x >= 0 && location.x < SCREEN_TILE_WIDTH &&
            location.y >= 0 && location.y < SCREEN_TILE_HEIGHT;
    };

    auto visibleCharacters = filter<Character>(gameState.getCharacters(), isInView);

    oamClear(&oamMain, 0, 0);
    int oamId = 0;
    for (Character& character : visibleCharacters) {
        u16* sprite = spriteRepository.getSprite(character.getType());
        Vec2 location = character.getLocation() - gameState.getCameraLocation();

        oamSet(&oamMain, oamId,
            location.x * TILE_SIZE, location.y * TILE_SIZE,
            0, 0, SpriteSize_16x16, SpriteColorFormat_16Color, sprite, 0, false, false, false, false, false);
        oamId++;
    }

    // Render game world (bottom screen?)
    // Render HUD (top screen?)

    oamUpdate(&oamMain);
}