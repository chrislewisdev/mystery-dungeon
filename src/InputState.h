#pragma once

struct InputState {
    bool a, b, x, y;
    bool up, down, left, right;
    bool leftBumper, rightBumper;
    bool start, select;

    static InputState getInputState();
    void printState();
};