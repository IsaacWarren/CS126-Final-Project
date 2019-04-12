#pragma once

#include "ofMain.h"
#include "player.h"
#include "ball.h"

class Pong {
private:
    Player player1;
    Player player2;
    int player1score;
    int player2score;
    Ball ball;
    int lastserv;

    const int BOARDHEIGHT = 720;
    const int BOARDWIDTH = 1280;
    const int WINNINGSCORE = 7;

    void UpdateScore();
    void UpdateBall();
public:
    static int GetBoardHeight() {return 720;};
    static int GetBoardWidth() {return 1280;};
    Pong();
    void Update();
    Player& GetPlayer1();
    Player& GetPlayer2();
    const Ball& GetBall() const;
    int GetPlayer1Score() const;
    int GetPlayer2Score() const;
    void ResetPlayer1Score();
    void ResetPlayer2Score();
    const int GetWinningScore() const;
    void ResetPositions();
};