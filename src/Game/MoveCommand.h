#pragma once

#include "Core/Vec2.h"
#include "Game/Command.h"
#include "Game/Character.h"

class MoveCommand : public Command {
    private:
        Vec2 delta;
    public:
        MoveCommand(Character& target, Vec2 delta) : Command(target), delta(delta) {}
        void apply() {
            Vec2 currentLocation = target.getLocation();
            target.setLocation(currentLocation.x + delta.x, currentLocation.y + delta.y);
        }
};