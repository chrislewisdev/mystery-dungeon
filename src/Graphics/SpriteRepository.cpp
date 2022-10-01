#include "SpriteRepository.h"

SpriteRepository::SpriteRepository(OamState* oam) : oam(oam) {}

void SpriteRepository::loadSprite(int typeId, MemoryBlock gfx) {
    // TODO: Support different sprite sizes?
    u16* sprite = oamAllocateGfx(oam, SpriteSize_16x16, SpriteColorFormat_16Color);
    dmaCopy(gfx.source, sprite, gfx.size);
    sprites[typeId] = sprite;
}

u16* SpriteRepository::getSprite(int typeId) {
    // TODO: What if we request a sprite that isn't currently loaded?
    return sprites.at(typeId);
}