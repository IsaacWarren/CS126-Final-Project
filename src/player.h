#pragma once

#include "ofMain.h"
#include "paddle.h"

class Player {
private:
    Paddle paddle = 0;
    int direction;
public:
    virtual ~Player(){};
    virtual void Update(const ofVec2f& ballposition) = 0;
    virtual void SetDirection(const int toset) = 0;
    virtual Paddle& GetPaddle() = 0;
};