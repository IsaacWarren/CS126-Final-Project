#include "pongai.h"


PongAI::PongAI(Player& player1toset, Player& player2toset) :player1(player1toset), player2(player2toset){
    generator.seed(time(NULL));
}


void PongAI::Update() {
    UpdateScore();
    UpdateBall();
    player1.Update(ball);
    player2.Update(ball);
    
}

Player& PongAI::GetPlayer1(){
    return player1;
}

Player& PongAI::GetPlayer2(){
    return player2;
}

const Ball& PongAI::GetBall() const {
    return ball;
}

int PongAI::GetPlayer1Score() const {
    return player1score;
}

int PongAI::GetPlayer2Score() const {
    return player2score;
}

void PongAI::ResetPlayer1Score() {
    player1score = 0;
}

void PongAI::ResetPlayer2Score() {
    player2score = 0;
}

void PongAI::UpdateScore() {
    float ballx = ball.GetPosition().x;
    if (ballx + ball.GetSize() >= BOARDWIDTH) {
        ++player1score;
        ResetPositions();
    } else if (ballx <= 0) {
        ++player2score;
        ResetPositions();
    }
}

void PongAI::UpdateBall() {
    ball.UpdatePosition();
    ofVec2f ballposition = ball.GetPosition();
    ofVec2f ballspeed = ball.GetSpeed();


    if (ballposition.y + ball.GetSize() >= BOARDHEIGHT) {
        ballspeed.y *= -1;
        ball.SetSpeed(ballspeed);
        return;
    }
    if (ballposition.y <= 0) {
        ballspeed.y *= -1;
        ball.SetSpeed(ballspeed);
        return;
    }

    if (ballposition.x + ball.GetSize() >= player2.GetPaddle().GetPosition().x && solidwall == true) {
        ballspeed.x *= -1;
        ball.SetSpeed(ballspeed);
        return;
    }

    ofVec2f player1position = player1.GetPaddle().GetPosition();
    ofVec2f player2position = player2.GetPaddle().GetPosition();

//https://gamedev.stackexchange.com/questions/4253/in-pong-how-do-you-calculate-the-balls-direction-when-it-bounces-off-the-paddl
    if (ballposition.x  <= player1position.x + player1.GetPaddle().GetWidth() &&
                            ballposition.y + ball.GetSize() >= player1position.y &&
                            ballposition.y <= player1position.y + player1.GetPaddle().GetHeight()) {
        float relativeintersecty = (player1position.y + (player1.GetPaddle().GetHeight()/2)) - (ballposition.y + ball.GetSize()/2);
        float normalizedrelativeintersectiony = (relativeintersecty/(player1.GetPaddle().GetHeight()/2));
        float bounceangle = normalizedrelativeintersectiony * ball.GetMaxBounceAngle();
        ballspeed.x = ball.GetStartingSpeed() * cos(bounceangle);
        ballspeed.y = ball.GetStartingSpeed() * sin(bounceangle) * -1;

        ball.SetSpeed(ballspeed);
        
        player1.AddHit();
    }

    if (ballposition.x  + ball.GetSize() >= player2position.x && ballposition.y + ball.GetSize() >= player2position.y &&
                            ballposition.y <= player2position.y + player1.GetPaddle().GetHeight()) {
        float relativeintersecty = (player2position.y + (player2.GetPaddle().GetHeight()/2)) - (ballposition.y + ball.GetSize()/2);
        float normalizedrelativeintersectiony = (relativeintersecty/(player2.GetPaddle().GetHeight()/2));
        float bounceangle = normalizedrelativeintersectiony * ball.GetMaxBounceAngle();
        ballspeed.x = ball.GetStartingSpeed() * cos(bounceangle) * -1;
        ballspeed.y = ball.GetStartingSpeed() * sin(bounceangle) * -1;

        ball.SetSpeed(ballspeed);

        player2.AddHit();
    }
}

void PongAI::ResetPositions() {
    ofVec2f ballposition;
    ballposition.set(PongAI::GetBoardWidth() / 2, PongAI::GetBoardHeight() / 2);
    ofVec2f ballspeed;

    lastserv *= -1;
    std::uniform_real_distribution<float> distribution(-ball.GetMaxBounceAngle(), ball.GetMaxBounceAngle());
    float bounceangle = distribution(generator);
    ballspeed.set(ball.GetStartingSpeed() * cos(bounceangle) * -1, ball.GetStartingSpeed() * sin(bounceangle) * -1);

    ball.SetPosition(ballposition);
    ball.SetSpeed(ballspeed);

    player1.GetPaddle().SetPosition(player1.GetPaddle().GetPosition().x,
                        BOARDHEIGHT / 2 - player1.GetPaddle().GetHeight() / 2);
    player2.GetPaddle().SetPosition(player2.GetPaddle().GetPosition().x,
                        BOARDHEIGHT / 2 - player2.GetPaddle().GetHeight() / 2);
}

const int PongAI::GetWinningScore() const {
    return WINNINGSCORE;
}

bool PongAI::IsWinner() const {
    return player1score >= WINNINGSCORE || player2score >= WINNINGSCORE ||
                 ((player1.GetHits() > hitstowin || player2.GetHits() > hitstowin));
}

Player& PongAI::GetWinner() const {
    if (player1.GetHits() > player2.GetHits()) {
        return player1;
    }

    return player2;
}

int PongAI::GetWinnerHits() const {
    if (player1.GetHits() > player2.GetHits()) {
        return player1.GetHits();
    } else {
        return player2.GetHits();
    }
}