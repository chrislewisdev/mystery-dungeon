#pragma once

#include "Core/Vec2.h"

class Character {
    private:
        const int id;
        const int type;
        Vec2 location;
    public:
        Character(int id, int type) : id(id), type(type) {}
        int getId() { return id; }
        int getType() { return type; }
        Vec2 getLocation() { return location; }
        void setLocation(int x, int y) { location.x = x; location.y = y; }
};