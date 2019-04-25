#pragma once

#include "ofMain.h"
#include "paddle.h"
#include "ball.h"

class Player {
private:
    Paddle paddle = 0;
    int direction;
    int hits = 0;
public:
    virtual ~Player(){};
    virtual void Update(const Ball& ball) = 0;
    virtual void SetDirection(const int toset) = 0;
    virtual Paddle& GetPaddle() = 0;
    virtual Player* GenerateOffspring() = 0;
    virtual bool IsHuman() const = 0;
    int GetHits() const {return hits;};
    void AddHit() {++hits;};
};