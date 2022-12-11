#include "PlayerController.h"
#include "Game/MoveCommand.h"
#include "Game/GameState.h"

#include <stdio.h>

using namespace std;

unique_ptr<MoveCommand> move(GameState& gameState, Character& character, int x, int y) {
    Vec2 delta(x, y);

    // Check that terrain at destination is walkable
    if (gameState.getMap().getTile(character.getLocation() + delta).getAttributes().isSolid) {
        return nullptr;
    }

    return make_unique<MoveCommand>(character, Vec2(x, y));
}

unique_ptr<Command> PlayerController::getCommand(InputState& inputState, GameState& gameState, Character& character) {
    if (inputState.left) {
        return move(gameState, character, -1, 0);
    } else if (inputState.right) {
        return move(gameState, character, 1, 0);
    } else if (inputState.up) {
        return move(gameState, character, 0, -1);
    } else if (inputState.down) {
        return move(gameState, character, 0, 1);
    }
    
    return nullptr;
}