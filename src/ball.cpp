#include "ball.h"
#include "pongai.h"

Ball::Ball() {
    position.push_back(PongAI::GetBoardWidth() / 2);
    position.push_back(PongAI::GetBoardHeight() / 2);

    speed.push_back(STARTINGSPEED);
    speed.push_back(0);
}

void Ball::UpdatePosition() {
    position[0] += speed[0];
    position[1] += speed[1];
}

const std::vector<float>& Ball::GetPosition() const {
    return position;
}

void Ball::SetSpeed(const std::vector<float>& newspeed) {
    speed[0] = newspeed[0];
    speed[1] = newspeed[1];
}

const std::vector<float>& Ball::GetSpeed() const {
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

void Ball::SetPosition(std::vector<float>& newposition) {
    position[0] = newposition[0];
    position[1] = newposition[1];
}