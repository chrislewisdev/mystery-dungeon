#include "GameState.h"
#include <stdio.h>
#include <memory>
#include "Game/Controller.h"
#include "Game/Command.h"

using namespace std;

GameState::GameState(MapGenerator& mapGenerator): map(mapGenerator.generateMap()), mapGenerator(mapGenerator) {
    characters.reserve(20);
    // initialiseFloor();
}

int GameState::getNextTurnIndex() {
    return turnIndex + 1 >= characters.size() ? 0 : turnIndex + 1;
}

// TODO: move this somewhere to share between here and map generation
Vec2 generateSpawnPoint(Rect2 room) {
    return room.location + Vec2(rand() % room.size.x, rand() % (room.size.y - 1) + 1);
}

void GameState::initialiseFloor() {
    for (Rect2 room : map.getRooms()) {
        Vec2 spawnPoint = generateSpawnPoint(room);
        spawnAt(1, spawnPoint.x, spawnPoint.y, idleController, false);
    }
}

// TODO: cleanupFloor

Map& GameState::getMap() {
    return map;
}

std::vector<Character>& GameState::getCharacters() {
    return characters;
}

Character& GameState::spawnAt(int type, int x, int y, Controller& controller, bool isPlayer) {
    Character character(idCounter++, type, controller, isPlayer);
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

    // Player-specific checks - might want to make this more generic somehow
    if (currentTurnCharacter.getIsPlayer()) {
        MetaTile tile = map.getTile(currentTurnCharacter.getLocation());
        if (tile.getAttributes().isStairs) {
            // Need to work out how we will reset and re-generate the floor...
            map = mapGenerator.generateMap();
            currentTurnCharacter.setLocation(map.getStartingLocation());
        }
    }

    // Update camera
    Vec2 newCameraLocation = trackTarget(camera, cameraTarget);
    if (newCameraLocation != camera) {
        camera = newCameraLocation;
        map.renderMetamap(camera);
    }

    iprintf("Room count: %d\n", map.getRooms().size());
    iprintf("Char count: %d", characters.size());
}

void GameState::setCameraTarget(Character* target) {
    cameraTarget = target;
}

Vec2 GameState::getCameraLocation() {
    return camera;
}