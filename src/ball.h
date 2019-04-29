#pragma once

#include <math.h>
#include <vector>

class Ball {
private:
    std::vector<float> position;
    std::vector<float> speed;

    const int STARTINGSPEED = 13;
    const int SIZE = 40;
    const float MAXBOUNCEANGLE = 4*M_PI/12;
public:
    Ball();
    void UpdatePosition();
    void SetPosition(std::vector<float>& newposition);
    const std::vector<float>& GetPosition() const;
    void SetSpeed(const std::vector<float>& newspeed);
    const std::vector<float>& GetSpeed() const;
    int GetSize() const;
    float GetMaxBounceAngle() const;
    int GetStartingSpeed() const;
};