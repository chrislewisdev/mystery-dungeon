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
        int getId() const { return id; }
        int getType() const { return type; }
        bool getIsPlayer() const { return isPlayer; }
        Vec2 getLocation() const { return location; }
        void setLocation(int x, int y) { location.x = x; location.y = y; }
        void setLocation(Vec2 l) { location = l; }
        Controller& getController() const { return controller; }
};