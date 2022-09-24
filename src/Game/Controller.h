#pragma once

#include <memory>

// Forward-declared because there is a circular dependency in these files
class Command;
class Character;

class Controller {
    public:
        virtual bool isReady(InputState& inputState, Character& character) = 0;
        virtual std::unique_ptr<Command> getCommand(InputState& inputState, Character& character) = 0;
};