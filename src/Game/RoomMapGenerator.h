#pragma once

#include "Game/MapGenerator.h"

// A simple map generator that creates an empty map with walls on each side
class RoomMapGenerator : public MapGenerator {
    private:
        MetaTileRepository& metaTileRepository;
    public:
        RoomMapGenerator(MetaTileRepository& metaTileRepository);
        virtual Map generateMap();
};