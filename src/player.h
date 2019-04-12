#pragma once

#include "ofMain.h"
#include "paddle.h"

class Player {
private:
    Paddle paddle;
    int direction;
public:
    Player(const int startx);
    void Update();
    void SetDirection(const int toset);
    Paddle& GetPaddle();
};