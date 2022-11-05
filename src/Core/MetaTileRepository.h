#pragma once

#include "Core/MetaTile.h"
#include <map>

class MetaTileRepository {
    private:
        std::map<MetaTileId, MetaTile> metaTiles;
        u16 ceilingTileId, floorTileId, wallTileId;
    public:
        void store(MetaTile metaTile);
        MetaTile& get(MetaTileId id);
        u16 getCeilingTileId() { return ceilingTileId; }
        void setCeilingTileId(u16 id) { ceilingTileId = id; }
        u16 getFloorTileId() { return floorTileId; }
        void setFloorTileId(u16 id) { floorTileId = id; }
        u16 getWallTileId() { return wallTileId; }
        void setWallTileId(u16 id) { wallTileId = id; }
};
