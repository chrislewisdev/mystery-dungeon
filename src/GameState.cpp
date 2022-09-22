#include "GameState.h"
#include <stdio.h>

Map& GameState::getMap() {
    return map;
}

std::vector<Character>& GameState::getCharacters() {
    return characters;
}

void GameState::spawnAt(int type, int x, int y) {
    Character character(idCounter++, type);
    character.setLocation(x, y);
    characters.push_back(character);
}

void GameState::update(InputState& inputState) {
    inputState.printState();
    iprintf("%ld", __cplusplus);
}