#pragma once

#include "ofMain.h"
#include "player.h"
#include "ball.h"
#include "ai.h"

class PongAI {
private:
    Player& player1;
    Player& player2;
    int player1score = 0;
    int player2score = 0;
    Ball ball;
    int lastserv = 1;

    const int BOARDHEIGHT = 720;
    const int BOARDWIDTH = 1280;
    const int WINNINGSCORE = 3;
    
    void UpdateScore();
    void UpdateBall();
public:
    static int GetBoardHeight() {return 720;};
    static int GetBoardWidth() {return 1280;};
    PongAI(Player& player1, Player& player2);
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
    bool IsWinner() const;
    Player& GetWinner() const;
};