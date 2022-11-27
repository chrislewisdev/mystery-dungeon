#pragma once

#include "Core/Vec2.h"
#include "Game/Controller.h"

class Character {
    private:
        const int id;
        const int type;
        Vec2 location;
        Controller& controller;
        bool isPlayer;
    public:
        Character(int id, int type, Controller& controller, bool isPlayer)
            : id(id), type(type), controller(controller), isPlayer(isPlayer) {}
        int getId() { return id; }
        int getType() { return type; }
        bool getIsPlayer() { return isPlayer; }
        Vec2 getLocation() { return location; }
        void setLocation(int x, int y) { location.x = x; location.y = y; }
        void setLocation(Vec2 l) { location = l; }
        Controller& getController() { return controller; }
};