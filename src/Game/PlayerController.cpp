#include "PlayerController.h"
#include "Game/MoveCommand.h"

using namespace std;

bool PlayerController::isReady(InputState& inputState, Character& character) {
    return true;
}

unique_ptr<Command> PlayerController::getCommand(InputState& inputState, Character& character) {
    return make_unique<MoveCommand>(character, Vec2(1, 0));
}