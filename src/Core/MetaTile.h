#pragma once

#include <nds.h>

typedef u16 MetaTileId;

struct MetaTileAttributes {
    bool isSolid;
};

class MetaTile {
    private:
        MetaTileId id;
        MetaTileAttributes attributes;
        u16 topLeft, topRight, bottomLeft, bottomRight;
    public:
        MetaTile() {}
        MetaTile(MetaTileId id, u16 topLeft, u16 topRight, u16 bottomLeft, u16 bottomRight) 
            : id(id), topLeft(topLeft), topRight(topRight), bottomLeft(bottomLeft), bottomRight(bottomRight) {}
        MetaTileId getId() { return id; }
        u16 getTopLeftTile() { return topLeft; }
        u16 getTopRightTile() { return topRight; }
        u16 getBottomLeftTile() { return bottomLeft; }
        u16 getBottomRightTile() { return bottomRight; }
        const MetaTileAttributes& getAttributes() { return attributes; }
};