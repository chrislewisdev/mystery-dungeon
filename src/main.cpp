// System
#include <nds.h>
#include <stdio.h>
#include <ctime>
// Internal
#include "Core/InputState.h"
#include "Core/MemoryBlock.h"
#include "Game/GameState.h"
#include "Game/PlayerController.h"
#include "Game/ConnectedRoomsMapGenerator.h"
#include "Graphics/GameRenderer.h"
// GFX
#include "tiles.h"
#include "palette-endesga.h"
#include "palette-sweetie.h"
#include "princess.h"
#include "goblin.h"
#include "slime.h"

void setupMetaTiles(MetaTileRepository& metaTileRepository) {
    MetaTile ceiling(0);
    MetaTile floor(1);
    MetaTile wall(2);
    MetaTile stairs(3);

    metaTileRepository.store(ceiling.asSolid());
    metaTileRepository.store(floor);
    metaTileRepository.store(wall.asSolid());
    metaTileRepository.store(stairs.asStairs());

    metaTileRepository.setCeilingTileId(ceiling.getId());
    metaTileRepository.setFloorTileId(floor.getId());
    metaTileRepository.setWallTileId(wall.getId());
    metaTileRepository.setStairsTileId(stairs.getId());
}

int main() {
    srand(time(0));

    MemoryBlock spritePalette(palette_sweetiePal, palette_sweetiePalLen);
    MemoryBlock bgPalette(tilesPal, tilesPalLen);
    MemoryBlock tiles(tilesTiles, tilesTilesLen);
    MemoryBlock character(princessTiles, princessTilesLen);
    MemoryBlock goblin(goblinTiles, goblinTilesLen);
    MemoryBlock slime(slimeTiles, slimeTilesLen);

    PlayerController playerController;
    
    MetaTileRepository metaTileRepository;
    setupMetaTiles(metaTileRepository);

    ConnectedRoomsMapGenerator mapGenerator(metaTileRepository);
    GameState gameState(mapGenerator);
    // TODO: Spawn the character based on map info. This should probably be moved into some kind of GameState method to initialise a floor!!!
    Character& player = gameState.spawnAt(0, 4, 4, playerController);
    player.setLocation(gameState.getMap().getStartingLocation());
    // gameState.spawnAt(1, 8, 8, playerController);
    // gameState.spawnAt(2, 8, 4, playerController);

    // THIS BREAKS IF THE CHARACTERS VECTOR REALLOCATES AND THE PLAYER MOVES IN MEMORY
    // Consider: setting an id of the character to track instead of a raw pointer
    gameState.setCameraTarget(&player);

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