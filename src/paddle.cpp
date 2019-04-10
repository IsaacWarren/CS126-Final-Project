#include "paddle.h"
#include "pong.h"

Paddle::Paddle(const int startx) {
    position.set(startx, 285);
}

void Paddle::MoveUp() {
    if (position.y + HEIGHT <= Pong::GetBoardHeight()) {
        position.y += MOVERATE;
    }
}

void Paddle::MoveDown() {
    if (position.y >= 0) {
        position.y -= MOVERATE;
    }
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

void Paddle::SetPosition(ofVec2f& newposition) {
    position.x = newposition.x;
    position.y = newposition.y;
}