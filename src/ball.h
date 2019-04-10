#pragma once

#include <math.h>

#include "ofMain.h"

class Ball {
private:
    ofVec2f position;
    ofVec2f speed;

    const int STARTINGSPEED = 10;
    const int SIZE = 40;
    const float MAXBOUNCEANGLE = 4*PI/12;
public:
    Ball();
    void UpdatePosition();
    void SetPosition(ofVec2f& newposition);
    const ofVec2f& GetPosition() const;
    void SetSpeed(const ofVec2f& newspeed);
    const ofVec2f& GetSpeed() const;
    int GetSize() const;
    float GetMaxBounceAngle() const;
    int GetStartingSpeed() const;
};