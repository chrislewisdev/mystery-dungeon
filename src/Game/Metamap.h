#pragma once

#include <nds.h>
#include <memory>

class Metamap {
    private:
        u16 width, height;
        std::unique_ptr<u16[]> contents;
    public:
        Metamap(u16 width, u16 height);
        Metamap(Metamap& other);
        u16 getWidth();
        u16 getHeight();
        u16 getTile(u16 x, u16 y);
        void fill(u16 tileId);
        void fill(u16 x, u16 y, u16 length, u16 tileId);
        void setTile(u16 x, u16 y, u16 tileId);
};
