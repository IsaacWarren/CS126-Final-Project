#include "ponggame.h"



void PongGame::setup() {
    ofSetWindowTitle("Pong");
    ofBackground(0,0,0);
    for (int i = 0; i < POPULATIONSIZE; i++) {
        if (i % 2 == 0) {
            players.push_back(new AI(0));
        } else {
            players.push_back(new Human(1240));
        }
    }
    pong = new PongAI(*players[0], *players[1]);
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
    if (gamestate == TWOAI || gamestate == MIXED || gamestate == TWOHUMAN) {
        DrawRunning();
    } else if (gamestate == COMPLETED) {
        DrawCompleted();
    }

    if (gamestate == TWOAI) {
        DrawTwoAI();
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

void PongGame::DrawTwoAI() {
    ofSetColor(255,255,255);
    std::string matchstring = "Match: " + std::to_string(match);
    std::string generationstring = "Generation: " + std::to_string(generation);
    ofDrawBitmapString(matchstring, PongAI::GetBoardWidth() / 2 - 100, 100);
    ofDrawBitmapString(generationstring, PongAI::GetBoardWidth() / 2 - 100, 120);
}

void PongGame::Reset() {
    Player *player1 = players[match * 2];
    Player *player2 = players[match * 2 + 1];

    players[match * 2] = (pong->GetWinner().GenerateOffspring());
    players[match * 2 + 1] = (pong->GetWinner().GenerateOffspring());

    if (pong != nullptr) {
        delete pong;
    }
    delete player1;
    delete player2;

    UpdateMatchGeneration();

    players[match * 2]->GetPaddle().SetPosition(0, PongAI::GetBoardHeight() / 2);
    players[match * 2 + 1]->GetPaddle().SetPosition(1240, PongAI::GetBoardHeight() / 2);

 
    pong = new PongAI(*players[match * 2], *players[match * 2 + 1]);
    gamestate = TWOAI;
}

void PongGame::UpdateMatchGeneration() {
    match++;

    if (match == POPULATIONSIZE / 2) {
        match  = 0;
        generation++;
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(players), std::end(players), rng);
    }
}