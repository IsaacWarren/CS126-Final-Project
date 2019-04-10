#include "pong.h"

Pong::Pong() :player1(0), player2(BOARDWIDTH - (player1.GetPaddle().GetWidth())) {}

void Pong::Update() {

}

Player& Pong::GetPlayer1(){
    return player1;
}

Player& Pong::GetPlayer2(){
    return player2;
}

const Ball& Pong::GetBall() const {
    return ball;
}

int Pong::GetPlayer1Score() const {
    return player1score;
}

int Pong::GetPlayer2Score() const {
    return player2score;
}