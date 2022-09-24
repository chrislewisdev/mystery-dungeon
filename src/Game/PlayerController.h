#pragma once

#include "Core/InputState.h"
#include "Game/Controller.h"

class PlayerController : public Controller {
    public:
        PlayerController() {}
        virtual bool isReady(InputState& inputState, Character& character);
        virtual std::unique_ptr<Command> getCommand(InputState& inputState, Character& character);
};