#pragma once

#include "Game/Command.h"

class WaitCommand : public Command {
    public:
        WaitCommand(Character& target) : Command(target) {}
        void apply() { /*Do nothing*/ }
};
