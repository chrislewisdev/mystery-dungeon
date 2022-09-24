#include "PlayerController.h"
#include "Game/MoveCommand.h"

using namespace std;

unique_ptr<MoveCommand> move(Character& character, int x, int y) {
    return make_unique<MoveCommand>(character, Vec2(x, y));
}

unique_ptr<Command> PlayerController::getCommand(InputState& inputState, Character& character) {
    if (inputState.left) {
        return move(character, -1, 0);
    } else if (inputState.right) {
        return move(character, 1, 0);
    } else if (inputState.up) {
        return move(character, 0, -1);
    } else if (inputState.down) {
        return move(character, 0, 1);
    }
    
    return nullptr;
}