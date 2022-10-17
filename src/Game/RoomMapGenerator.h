#pragma once

#include "Game/MapGenerator.h"

// A simple map generator that creates an empty map with walls on each side
class RoomMapGenerator : public MapGenerator {
    public:
        virtual Map generateMap();
};