// System
#include <nds.h>
#include <stdio.h>
// Internal
#include "Core/InputState.h"
#include "Core/MemoryBlock.h"
#include "Game/GameState.h"
#include "Game/PlayerController.h"
#include "Graphics/GameRenderer.h"
// GFX
#include "map.h"
#include "palette-endesga.h"
#include "palette-sweetie.h"
#include "princess.h"
#include "goblin.h"
#include "slime.h"

int main() {
    // Placeholder map data
    // MemoryBlock spritePalette(palette_endesgaPal, palette_endesgaPalLen);
    MemoryBlock spritePalette(palette_sweetiePal, palette_sweetiePalLen);
    // MemoryBlock spritePalette(princessPal, princessPalLen);
    MemoryBlock bgPalette(mapPal, mapPalLen);
    MemoryBlock tiles(mapTiles, mapTilesLen);
    MemoryBlock mapData(mapMap, mapMapLen);
    MemoryBlock character(princessTiles, princessTilesLen);
    MemoryBlock goblin(goblinTiles, goblinTilesLen);
    MemoryBlock slime(slimeTiles, slimeTilesLen);

    PlayerController playerController;
    
    GameState gameState;
    gameState.getMap().load(mapData);
    gameState.spawnAt(0, 4, 4, playerController);
    gameState.spawnAt(1, 8, 8, playerController);
    gameState.spawnAt(2, 8, 4, playerController);

    GameRenderer renderer(&oamMain);
    renderer.init(bgPalette, spritePalette, tiles);
    renderer.getSpriteRepository().loadSprite(0, character);
    renderer.getSpriteRepository().loadSprite(1, goblin);
    renderer.getSpriteRepository().loadSprite(2, slime);

    // TODO: Devise a more refined method for debug output once sub display is utilised
    consoleDemoInit();

    while (true) {
        // TODO: Abstract into app states for separation between game/menu logic?
        consoleClear();

        InputState inputState = InputState::getInputState();
        gameState.update(inputState);
        swiWaitForVBlank();
        renderer.render(gameState);
    }

    return 0;
}