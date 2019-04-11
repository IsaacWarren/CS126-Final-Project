#pragma once

#include "ofMain.h"
#include "player.h"
#include "ball.h"
#include "ai.h"

class PongAI {
private:
    AI player1;
    Player player2;
    int player1score;
    int player2score;
    Ball ball;
    int lastserv = 1;

    const int BOARDHEIGHT = 720;
    const int BOARDWIDTH = 1280;
    const int WINNINGSCORE = 7;
    
    void UpdateScore();
    void UpdateBall();
    void ResetPositions();
public:
    static int GetBoardHeight() {return 720;};
    static int GetBoardWidth() {return 1280;};
    PongAI();
    void Update();
    AI& GetPlayer1();
    Player& GetPlayer2();
    const Ball& GetBall() const;
    int GetPlayer1Score() const;
    int GetPlayer2Score() const;
};