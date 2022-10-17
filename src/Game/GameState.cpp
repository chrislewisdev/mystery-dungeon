#include "GameState.h"
#include <stdio.h>
#include <memory>
#include "Game/Controller.h"
#include "Game/Command.h"

using namespace std;

GameState::GameState(MapGenerator& mapGenerator): map(mapGenerator.generateMap()) {}

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
    Character& currentTurnCharacter = characters.at(turnIndex);
    Controller& controller = currentTurnCharacter.getController();
    unique_ptr<Command> command = controller.getCommand(inputState, *this, currentTurnCharacter);
    if (command) {
        command.get()->apply();
        turnIndex = getNextTurnIndex();
    }
}