#pragma once

#include <nds.h>

typedef u16 MetaTileId;

struct MetaTileAttributes {
    bool isSolid;
    bool isStairs;
};

class MetaTile {
    private:
        MetaTileId id;
        MetaTileAttributes attributes;
        u16 topLeft, topRight, bottomLeft, bottomRight;
    public:
        MetaTile() {}
        MetaTile(MetaTileId id) 
            : id(id), topLeft(id * 4), topRight(id * 4 + 1), bottomLeft(id * 4 + 2), bottomRight(id * 4 + 3) {}
        MetaTileId getId() { return id; }
        u16 getTopLeftTile() { return topLeft; }
        u16 getTopRightTile() { return topRight; }
        u16 getBottomLeftTile() { return bottomLeft; }
        u16 getBottomRightTile() { return bottomRight; }
        const MetaTileAttributes& getAttributes() { return attributes; }
        MetaTile& asSolid() { attributes.isSolid = true; return *this; }
        MetaTile& asStairs() { attributes.isStairs = true; return *this; }
};