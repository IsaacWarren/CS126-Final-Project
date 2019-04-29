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
    float ballx = ball.GetPosition()[0];
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
    std::vector<float> ballposition = ball.GetPosition();
    std::vector<float> ballspeed = ball.GetSpeed();


    if (ballposition[1] + ball.GetSize() >= BOARDHEIGHT) {
        ballspeed[1] *= -1;
        ball.SetSpeed(ballspeed);
        return;
    }
    if (ballposition[1] <= 0) {
        ballspeed[1] *= -1;
        ball.SetSpeed(ballspeed);
        return;
    }

    if (ballposition[0] + ball.GetSize() >= player2.GetPaddle().GetPosition()[0] && solidwall == true) {
        ballspeed[0] *= -1;
        ball.SetSpeed(ballspeed);
        return;
    }

    std::vector<float> player1position = player1.GetPaddle().GetPosition();
    std::vector<float> player2position = player2.GetPaddle().GetPosition();

//https://gamedev.stackexchange.com/questions/4253/in-pong-how-do-you-calculate-the-balls-direction-when-it-bounces-off-the-paddl
    if (ballposition[0]  <= player1position[0] + player1.GetPaddle().GetWidth() &&
                            ballposition[1] + ball.GetSize() >= player1position[1] &&
                            ballposition[1] <= player1position[1] + player1.GetPaddle().GetHeight()) {
        float relativeintersecty = (player1position[1] + (player1.GetPaddle().GetHeight()/2)) - (ballposition[1] + ball.GetSize()/2);
        float normalizedrelativeintersectiony = (relativeintersecty/(player1.GetPaddle().GetHeight()/2));
        float bounceangle = normalizedrelativeintersectiony * ball.GetMaxBounceAngle();
        ballspeed[0] = ball.GetStartingSpeed() * cos(bounceangle);
        ballspeed[1] = ball.GetStartingSpeed() * sin(bounceangle) * -1;

        ball.SetSpeed(ballspeed);
        
        player1.AddHit();
    }

    if (ballposition[0]  + ball.GetSize() >= player2position[0] && ballposition[1] + ball.GetSize() >= player2position[1] &&
                            ballposition[1] <= player2position[1] + player1.GetPaddle().GetHeight()) {
        float relativeintersecty = (player2position[1] + (player2.GetPaddle().GetHeight()/2)) - (ballposition[1] + ball.GetSize()/2);
        float normalizedrelativeintersectiony = (relativeintersecty/(player2.GetPaddle().GetHeight()/2));
        float bounceangle = normalizedrelativeintersectiony * ball.GetMaxBounceAngle();
        ballspeed[0] = ball.GetStartingSpeed() * cos(bounceangle) * -1;
        ballspeed[1] = ball.GetStartingSpeed() * sin(bounceangle) * -1;

        ball.SetSpeed(ballspeed);

        player2.AddHit();
    }
}

void PongAI::ResetPositions() {
    std::vector<float> ballposition;
    ballposition.push_back(PongAI::GetBoardWidth() / 2);
    ballposition.push_back(PongAI::GetBoardHeight() / 2);
    std::vector<float> ballspeed;

    lastserv *= -1;
    std::uniform_real_distribution<float> distribution(-ball.GetMaxBounceAngle(), ball.GetMaxBounceAngle());
    float bounceangle = distribution(generator);
    ballspeed.push_back(ball.GetStartingSpeed() * cos(bounceangle) * -1);
    ballspeed.push_back(ball.GetStartingSpeed() * sin(bounceangle) * -1);

    ball.SetPosition(ballposition);
    ball.SetSpeed(ballspeed);

    player1.GetPaddle().SetPosition(player1.GetPaddle().GetPosition()[0],
                        BOARDHEIGHT / 2 - player1.GetPaddle().GetHeight() / 2);
    player2.GetPaddle().SetPosition(player2.GetPaddle().GetPosition()[0],
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