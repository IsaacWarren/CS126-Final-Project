#include "player.h"

Player::Player(const int startx) : paddle(startx) {}

void Player::Update() {
    if (direction > 0) {
        paddle.MoveUp();
    } else if (direction < 0) {
        paddle.MoveDown();
    }
}

void Player::SetDirection(const int toset) {
    direction = toset;
}

const Paddle& Player::GetPaddle() const {
    return paddle;
}