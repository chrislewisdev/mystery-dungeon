#include "Game/Metamap.h"

using namespace std;

Metamap::Metamap(u16 width, u16 height) : width(width), height(height) {
    contents = make_unique<u16[]>(width * height);
}

Metamap::Metamap(Metamap& other) 
    : width(other.getWidth()), height(other.getHeight()), contents(move(other.contents)) {}

u16 Metamap::getWidth() { return width; }
u16 Metamap::getHeight() { return height; }
u16 Metamap::getTile(u16 x, u16 y) { return contents.get()[y * width + x]; }

void Metamap::fill(u16 tileId) {
    dmaFillHalfWords(tileId, contents.get(), sizeof(u16) * width * height);
}

void Metamap::fill(u16 x, u16 y, u16 length, u16 tileId) {
    u16* address = contents.get() + (y * width) + x;
    dmaFillHalfWords(tileId, address, sizeof(u16) * length);
}

void Metamap::setTile(u16 x, u16 y, u16 tileId) {
    const int address = y * width + x;
    contents.get()[address] = tileId;
}

Metamap& Metamap::operator=(Metamap& other) {
    width = other.width;
    height = other.height;
    contents = move(other.contents);

    return *this;
}
