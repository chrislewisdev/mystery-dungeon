// System
#include <nds.h>
#include <stdio.h>
#include <vector>
#include <queue>
#include <map>
// Internal
#include "InputState.h"
// GFX
#include "map.h"
#include "palette.h"
#include "character.h"

#define TILE_SIZE 16

struct Vec2 {
    int x, y;
};

struct MemoryBlock {
    const void* source;
    const uint32 size;

    MemoryBlock(const void* source, const uint32 size) : source(source), size(size) {}
};

// class Command {
//     protected:
//         const Character* target;
//         Command(Character *character) : character(character) {}
//     public:
//         virtual void apply() = 0;
// };

// class Controller {

// };

class Character {
    private:
        const int id;
        const int type;
        Vec2 location;
    public:
        Character(int id, int type) : id(id), type(type) {}
        int getId() { return id; }
        int getType() { return type; }
        Vec2 getLocation() { return location; }
        void setLocation(int x, int y) { location.x = x; location.y = y; }
};

class Map {
    private:
        u16 mapVersion = 0;
        u16 virtualMap[1024];
    public:
        void load(const MemoryBlock& memory) {
            dmaCopy(memory.source, virtualMap, memory.size);
            mapVersion++;
        }
        void flushMap(u16* destination) {
            dmaCopy(virtualMap, destination, sizeof(virtualMap));
        }
        u16 getMapVersion() {
            return mapVersion;
        }
};

class GameState {
    private:
        Map map;
        std::vector<Character> characters;
        int turnIndex = 0;
        int idCounter = 0;
    public:
        Map& getMap() { return map; }
        std::vector<Character>& getCharacters() { return characters; }
        void spawnAt(int type, int x, int y) {
            Character character(idCounter++, type);
            character.setLocation(x, y);
            characters.push_back(character);
        }
        void update(InputState& inputState) {
            inputState.printState();
            iprintf("%ld", __cplusplus);
        }
};

class OamRepository {
    private:
        std::queue<int> availableOamIds;
        std::map<int, int> oamAllocations;
    public:
        OamRepository() {
            for (int i = 0; i < SPRITE_COUNT; i++) {
                availableOamIds.push(i);
            }
        }
        int getOrAllocateOamId(int characterId) {
            if (oamAllocations.find(characterId) != oamAllocations.end()) {
                return oamAllocations.at(characterId);
            } else {
                // TODO: Handle no available ids
                int oamId = availableOamIds.front();
                availableOamIds.pop();
                oamAllocations[characterId] = oamId;
                return oamId;
            }
        }
};

class SpriteRepository {
    private:
        OamState* oam;
        std::map<int, u16*> sprites;
    public:
        SpriteRepository(OamState* oam) : oam(oam) {}
        void loadSprite(int typeId, MemoryBlock gfx) {
            // TODO: Support different sprite sizes?
            u16* sprite = oamAllocateGfx(oam, SpriteSize_16x16, SpriteColorFormat_16Color);
            dmaCopy(gfx.source, sprite, gfx.size);
            sprites[typeId] = sprite;
        }
        u16* getSprite(int typeId) {
            // TODO: Would we ever request a sprite that isn't currently loaded?
            return sprites.at(typeId);
        }
};

class GameRenderer {
    private:
        int backgroundId = 0;
        u16 latestMapVersion = 0;
        OamRepository oamRepository;
        SpriteRepository spriteRepository;
    public:
        GameRenderer(OamState* oamMain) : spriteRepository(oamMain) {}
        SpriteRepository& getSpriteRepository() { return spriteRepository; }
        void init(const MemoryBlock& bgPalette, const MemoryBlock& spritePalette, const MemoryBlock& tiles){
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
        void render(GameState& gameState) {
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
};

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