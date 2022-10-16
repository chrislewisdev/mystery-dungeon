#pragma once

#include "Core/InputState.h"
#include "Game/Controller.h"
#include "Game/GameState.h"

class PlayerController : public Controller {
    public:
        PlayerController() {}
        virtual std::unique_ptr<Command> getCommand(InputState& inputState, GameState& gameState, Character& character);
};