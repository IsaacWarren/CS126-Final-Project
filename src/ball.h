#pragma once

#include "ofMain.h"

class Ball {
private:
    ofVec2f position;
    ofVec2f speed;
public:
    Ball();
    UpdatePosition();
    GetPosition();
};