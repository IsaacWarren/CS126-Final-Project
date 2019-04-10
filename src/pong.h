#pragma once

#include "ofMain.h"

class Pong {
private:
    Player player1;
    Player player2;
    int player1score;
    int player2score;
    Ball ball;
public:
    Play();
};