#include "human.h"

Human::Human(const int startx) : paddle(startx) {}

void Human::Update(const ofVec2f& balposition) {
    if (direction < 0) {
        paddle.MoveUp();
    } else if (direction > 0) {
        paddle.MoveDown();
    }
}

void Human::SetDirection(const int toset) {
    direction = toset;
}

Paddle& Human::GetPaddle() {
    return paddle;
}

Human* Human::GenerateOffspring() {
    return new Human(GetPaddle().GetPosition().x);
}
