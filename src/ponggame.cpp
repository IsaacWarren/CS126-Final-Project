#include "ponggame.h"


void PongGame::setup() {
    ofSetWindowTitle("Pong");
    ofBackground(0,0,0);
    players.push_back(new AI(0));
    players.push_back(new AI(1240));
    pong = new PongAI(*players[0], *players[1]);
    players.clear();
}

void PongGame::exit() {
    if (pong != nullptr) {
        delete pong;
    }

    for (Player* playerpointer : players) {
        if (playerpointer != nullptr) {
            delete playerpointer;
        }
    }
}

void PongGame::update() {
    if (gamestate == TWOAI) {
        pong->Update();
        CheckForWinner();
    }
}

void PongGame::draw() {
    if (gamestate == TWOAI) {
        DrawRunning();
    } else if (gamestate == COMPLETED) {
        DrawCompleted();
    }

}

void PongGame::keyPressed(int key) {
    if (key == 'r') {
        Reset();
    }

    if (key == OF_KEY_ESC) {
        ofExit();
    }

    if (key == 'w') {
        pong->GetPlayer1().SetDirection(1);
    }
    if (key == 's') {
        pong->GetPlayer1().SetDirection(-1);
    }
    if (key == OF_KEY_UP) {
        pong->GetPlayer2().SetDirection(1);
    }
    if (key == OF_KEY_DOWN) {
        pong->GetPlayer2().SetDirection(-1);
    }

}

void PongGame::keyReleased(int key) {
    if (key == OF_KEY_UP || key == OF_KEY_DOWN) {
        pong->GetPlayer2().SetDirection(0);
    }
    if (key == 'w' || key == 's') {
        pong->GetPlayer1().SetDirection(0);
    }
}

bool PongGame::CheckForWinner() {
    if (pong->IsWinner()) {
        Reset();
        return true;
    }

    return false;
}

void PongGame::DrawRunning() {
    ofSetColor(255,255,255);

    ofDrawRectangle(pong->GetBall().GetPosition(), pong->GetBall().GetSize(), pong->GetBall().GetSize());
    ofDrawRectangle(pong->GetPlayer1().GetPaddle().GetPosition(), pong->GetPlayer1().GetPaddle().GetWidth(),
                    pong->GetPlayer1().GetPaddle().GetHeight());
    ofDrawRectangle(pong->GetPlayer2().GetPaddle().GetPosition(), pong->GetPlayer2().GetPaddle().GetWidth(),
                     pong->GetPlayer2().GetPaddle().GetHeight());

    ofDrawBitmapString(pong->GetPlayer1Score(), 200, 100);
    ofDrawBitmapString(pong->GetPlayer2Score(), PongAI::GetBoardWidth() - 210, 100);
}

void PongGame::DrawCompleted() {
    ofSetColor(255,255,255);
    if (pong->GetPlayer1Score() > pong->GetPlayer2Score()) {
        ofDrawBitmapString("Player1 won press R to Reset", PongAI::GetBoardWidth() / 2 - 100, 100);
    } else {
        ofDrawBitmapString("Player2 won press R to Reset", PongAI::GetBoardWidth() / 2 - 100, 100);
    }
}

void PongGame::Reset() {
    delete pong;
    players.push_back(new AI(0));
    players.push_back(new AI(1240));
    pong = new PongAI(*players[0], *players[1]);
    players.clear();
    gamestate = TWOAI;
}