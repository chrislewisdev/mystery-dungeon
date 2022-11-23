#pragma once

#include "Core/Vec2.h"
#include "Game/Controller.h"

class Character {
    private:
        const int id;
        const int type;
        Vec2 location;
        Controller& controller;
    public:
        Character(int id, int type, Controller& controller) : id(id), type(type), controller(controller) {}
        int getId() { return id; }
        int getType() { return type; }
        Vec2 getLocation() { return location; }
        void setLocation(int x, int y) { location.x = x; location.y = y; }
        void setLocation(Vec2 l) { location = l; }
        Controller& getController() { return controller; }
};