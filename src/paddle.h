#pragma once

#include "ofMain.h"

class Paddle {
private:
    ofVec2f position;
public:
    Paddle();
    MoveUp();
    MoveDown();
    GetPosition();
};