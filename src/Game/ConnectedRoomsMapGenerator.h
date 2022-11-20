#pragma once

#include "Game/MapGenerator.h"

class ConnectedRoomsMapGenerator : public MapGenerator {
    private:
        MetaTileRepository& metaTileRepository;
    public:
        ConnectedRoomsMapGenerator(MetaTileRepository& metaTileRepository);
        virtual Map generateMap();
};
