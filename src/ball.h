#pragma once

#include "ofMain.h"

class Ball {
private:
    ofVec2f position;
    ofVec2f speed;
    const int STARTINGSPEED = 10;
    const int SIZE = 40;
public:
    Ball();
    void UpdatePosition();
    const ofVec2f& GetPosition() const;
    void SetSpeed(const ofVec2f& newspeed);
    const ofVec2f& GetSpeed() const;
};