#pragma once

#include "ofMain.h"

class Paddle {
private:
    ofVec2f position;
    const int MOVERATE = 10;
    const int HEIGHT  = 150;
    const int WIDTH = 40;
public:
    Paddle(const int startx);
    void MoveUp();
    void MoveDown();
    void StopMoving();
    const ofVec2f& GetPosition() const;
    void SetPosition(float newx, float newy);
    const int& GetHeight() const;
    const int& GetWidth() const;
};