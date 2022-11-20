#include "GameState.h"
#include <stdio.h>
#include <memory>
#include "Game/Controller.h"
#include "Game/Command.h"

using namespace std;

GameState::GameState(MapGenerator& mapGenerator): map(mapGenerator.generateMap()) {
    characters.reserve(20);
}

int GameState::getNextTurnIndex() {
    return turnIndex + 1 >= characters.size() ? 0 : turnIndex + 1;
}

Map& GameState::getMap() {
    return map;
}

std::vector<Character>& GameState::getCharacters() {
    return characters;
}

Character& GameState::spawnAt(int type, int x, int y, Controller& controller) {
    Character character(idCounter++, type, controller);
    character.setLocation(x, y);
    characters.push_back(character);
    return characters.back();
}

Vec2 trackTarget(Vec2 currentLocation, Character* targetCharacter) {
    int x = currentLocation.x, y = currentLocation.y;
    Vec2 target = targetCharacter->getLocation() - Vec2(8, 6);

    // Might want to tweak this bounding box at some point
    if (x < target.x - 2) x = target.x - 2;
    if (x > target.x + 3) x = target.x + 3;
    if (y < target.y - 2) y = target.y - 2;
    if (y > target.y + 3) y = target.y + 3;

    return Vec2(x, y);
}

void GameState::update(InputState& inputState) {
    // Process turn of current character
    Character& currentTurnCharacter = characters.at(turnIndex);
    Controller& controller = currentTurnCharacter.getController();
    unique_ptr<Command> command = controller.getCommand(inputState, *this, currentTurnCharacter);
    if (command) {
        command.get()->apply();
        turnIndex = getNextTurnIndex();
    }

    // Update camera
    Vec2 newCameraLocation = trackTarget(camera, cameraTarget);
    if (newCameraLocation != camera) {
        camera = newCameraLocation;
        map.renderMetamap(camera);
    }
}

void GameState::setCameraTarget(Character* target) {
    cameraTarget = target;
}

Vec2 GameState::getCameraLocation() {
    return camera;
}