#include "ball.h"
#include "pongai.h"

Ball::Ball() {
    position.set(PongAI::GetBoardWidth() / 2, PongAI::GetBoardHeight() / 2);
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