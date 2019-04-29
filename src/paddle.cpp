#include "paddle.h"
#include "pongai.h"

Paddle::Paddle(const int startx) {
    position.push_back(startx);
    position.push_back(STARTY);
}

void Paddle::MoveUp() {
    if (position[1] + HEIGHT <= PongAI::GetBoardHeight()) {
        position[1] += MOVERATE;
    }
}

void Paddle::MoveDown() {
    if (position[1] >= 0) {
        position[1] -= MOVERATE;
    }
}

const std::vector<float>& Paddle::GetPosition() const {
    return position;
}

const int& Paddle::GetHeight() const {
    return HEIGHT;
}

const int& Paddle::GetWidth() const {
    return WIDTH;
}

void Paddle::SetPosition(float newx, float newy) {
    position[0] = newx;
    position[1] = newy;
}