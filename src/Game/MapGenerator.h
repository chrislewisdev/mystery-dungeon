#pragma once

#include "Game/Map.h"

class MapGenerator {
    public:
        virtual Map generateMap() = 0;
};