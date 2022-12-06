#pragma once

#include <vector>
#include "Core/InputState.h"
#include "Game/Character.h"
#include "Game/Map.h"
#include "Game/MapGenerator.h"
#include "Game/IdleController.h"

class GameState {
    private:
        Map map;
        std::vector<Character> characters;
        unsigned int turnIndex = 0;
        int idCounter = 0;
        Vec2 camera;
        Character* cameraTarget;
        MapGenerator& mapGenerator;
        IdleController idleController;

        int getNextTurnIndex();
    public:
        void initialiseFloor();
        GameState(MapGenerator& mapGenerator);
        Map& getMap();
        std::vector<Character>& getCharacters();
        Character& spawnAt(int type, int x, int y, Controller& controller, bool isPlayer);
        void update(InputState& inputState);
        void setCameraTarget(Character* target);
        Vec2 getCameraLocation();
};