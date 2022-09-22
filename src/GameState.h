#pragma once

#include <vector>
#include "Character.h"
#include "InputState.h"
#include "Map.h"

class GameState {
    private:
        Map map;
        std::vector<Character> characters;
        int turnIndex = 0;
        int idCounter = 0;
    public:
        Map& getMap();
        std::vector<Character>& getCharacters();
        void spawnAt(int type, int x, int y);
        void update(InputState& inputState);
};