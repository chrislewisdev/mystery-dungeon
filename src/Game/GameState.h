#pragma once

#include <vector>
#include "Core/InputState.h"
#include "Game/Character.h"
#include "Game/Map.h"

class GameState {
    private:
        Map map;
        std::vector<Character> characters;
        unsigned int turnIndex = 0;
        int idCounter = 0;
        int getNextTurnIndex();
    public:
        Map& getMap();
        std::vector<Character>& getCharacters();
        void spawnAt(int type, int x, int y, Controller& controller);
        void update(InputState& inputState);
};