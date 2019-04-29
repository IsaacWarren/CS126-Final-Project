#pragma once

#include <vector>

class Paddle {
private:
    std::vector<float> position;

    const int MOVERATE = 10;
    const int HEIGHT = 150;
    const int WIDTH = 40;
    const int STARTY = 285;
public:
    Paddle(const int startx);
    void MoveUp();
    void MoveDown();
    void StopMoving();
    const std::vector<float>& GetPosition() const;
    void SetPosition(float newx, float newy);
    const int& GetHeight() const;
    const int& GetWidth() const;
};