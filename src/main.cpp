// System
#include <nds.h>
#include <stdio.h>
#include <vector>
#include <queue>
#include <map>
// Internal
#include "Core/InputState.h"
#include "Core/MemoryBlock.h"
#include "Game/GameState.h"
#include "Graphics/GameRenderer.h"
// GFX
#include "map.h"
#include "palette.h"
#include "character.h"

int main() {
    // Placeholder map data
    MemoryBlock spritePalette(palettePal, palettePalLen);
    MemoryBlock bgPalette(mapPal, mapPalLen);
    MemoryBlock tiles(mapTiles, mapTilesLen);
    MemoryBlock mapData(mapMap, mapMapLen);
    MemoryBlock character(characterTiles, characterTilesLen);
    
    GameState gameState;
    gameState.getMap().load(mapData);
    gameState.spawnAt(0, 4, 4);

    GameRenderer renderer(&oamMain);
    renderer.init(bgPalette, spritePalette, tiles);
    renderer.getSpriteRepository().loadSprite(0, character);

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