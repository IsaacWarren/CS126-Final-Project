#include "paddle.h"

Paddle::Paddle(const int startx) {
    position.set(startx, 0);
}

void Paddle::MoveUp() {
    position += MOVERATE;
}

void Paddle::MoveDown() {
    position -= MOVERATE;
}

const ofVec2f& Paddle::GetPosition() const {
    return position;
}

const int& Paddle::GetHeight() const {
    return HEIGHT;
}

const int& Paddle::GetWidth() const {
    return WIDTH;
}