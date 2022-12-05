#pragma once

#include "Game/Controller.h"
#include "Game/WaitCommand.h"

class IdleController : public Controller {
    public:
        std::unique_ptr<Command> getCommand(InputState& inputState, GameState& gameState, Character& character) {
            return std::make_unique<WaitCommand>(character);
        }
};
