#include "InputState.h"
#include <nds.h>
#include <stdio.h>

InputState InputState::getInputState() {
    scanKeys();
    uint32 input = keysCurrent();
    return InputState{
        .a              = (input & KEY_A) != 0,
        .b              = (input & KEY_B) != 0,
        .x              = (input & KEY_X) != 0,
        .y              = (input & KEY_Y) != 0,
        .up             = (input & KEY_UP) != 0,
        .down           = (input & KEY_DOWN) != 0,
        .left           = (input & KEY_LEFT) != 0,
        .right          = (input & KEY_RIGHT) != 0,
        .leftBumper     = (input & KEY_L) != 0,
        .rightBumper    = (input & KEY_R) != 0,
        .start          = (input & KEY_START) != 0,
        .select         = (input & KEY_SELECT) != 0,
    };
}

void InputState::printState() {
    iprintf("A:%d,B:%d,X:%d,Y:%d\nU:%d,D:%d,L:%d,R:%d\nLB:%d,RB:%d\nSTART:%d,SEL:%d\n",
        a, b, x, y,
        up, down, left, right,
        leftBumper, rightBumper,
        start, select
    );
}