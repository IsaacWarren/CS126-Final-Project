#include "ball.h"
#include "pong.h"

Ball::Ball() {
    position.set(Pong::GetBoardWidth() / 2, Pong::GetBoardHeight() / 2);
    speed.set(STARTINGSPEED, 0);
}

void Ball::UpdatePosition() {
    position.x += speed.x;
    position.y += speed.y;
}

const ofVec2f& Ball::GetPosition() const {
    return position;
}

void Ball::SetSpeed(const ofVec2f& newspeed) {
    speed.x = newspeed.x;
    speed.y = newspeed.y;
}

const ofVec2f& Ball::GetSpeed() const {
    return speed;
}

int Ball::GetSize() const {
    return SIZE;
}

float Ball::GetMaxBounceAngle() const {
    return MAXBOUNCEANGLE;
}

int Ball::GetStartingSpeed() const {
    return STARTINGSPEED;
}

void Ball::SetPosition(ofVec2f& newposition) {
    position.x = newposition.x;
    position.y = newposition.y;
}