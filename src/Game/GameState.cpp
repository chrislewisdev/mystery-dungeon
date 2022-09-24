#include "GameState.h"
#include <stdio.h>
#include <memory>
#include "Game/Controller.h"
#include "Game/Command.h"

using namespace std;

int GameState::getNextTurnIndex() {
    return turnIndex + 1 >= characters.size() ? 0 : turnIndex + 1;
}

Map& GameState::getMap() {
    return map;
}

std::vector<Character>& GameState::getCharacters() {
    return characters;
}

void GameState::spawnAt(int type, int x, int y, Controller& controller) {
    Character character(idCounter++, type, controller);
    character.setLocation(x, y);
    characters.push_back(character);
}

void GameState::update(InputState& inputState) {
    iprintf("%d\n", turnIndex);

    Character& currentTurnCharacter = characters.at(turnIndex);
    Controller& controller = currentTurnCharacter.getController();
    if (controller.isReady(inputState, currentTurnCharacter)) {
        unique_ptr<Command> command = controller.getCommand(inputState, currentTurnCharacter);
        command.get()->apply();
        
        turnIndex = getNextTurnIndex();
    }
}