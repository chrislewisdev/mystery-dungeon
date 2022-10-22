#pragma once

#include "Core/MetaTile.h"
#include <map>

class MetaTileRepository {
    private:
        std::map<MetaTileId, MetaTile> metaTiles;
    public:
        void store(MetaTile metaTile);
        MetaTile& get(MetaTileId id);
};
