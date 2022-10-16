#pragma once

#include <memory>

// Forward-declared because there is a circular dependency in these files
class Command;
class Character;
class GameState;

class Controller {
    public:
        virtual std::unique_ptr<Command> getCommand(InputState& inputState, GameState& gameState, Character& character) = 0;
};