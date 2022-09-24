#pragma once

#include "Core/InputState.h"
#include "Game/Controller.h"

class PlayerController : public Controller {
    public:
        PlayerController() {}
        virtual std::unique_ptr<Command> getCommand(InputState& inputState, Character& character);
};