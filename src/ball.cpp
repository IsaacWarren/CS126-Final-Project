#include "ball.h"
#include "pong.h"

Ball::Ball() {
    position.set(Pong::GetBoardWidth() / 2, Pong::GetBoardHeight() / 2);
    speed.set(10, 0);
}

void Ball::UpdatePosition() {
    position.x += speed.x;
    position.y += speed.y;
}

const ofVec2f& Ball::GetPosition() const {
    return position;
}

void Ball::SetSpeed(const ofVec2f& newspeed) {
    speed = newspeed;
}

const ofVec2f& Ball::GetSpeed() const {
    return speed;
}