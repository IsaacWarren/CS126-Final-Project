#include "ponggame.h"



void PongGame::setup() {
    ofSetWindowTitle("Pong");
    ofBackground(0,0,0);
    for (int i = 0; i < POPULATIONSIZE; i++) {
        if (i % 2 == 0) {
            players.push_back(new AI(0));
        } else {
            players.push_back(new AI(1240));
        }
    }
    pong = new PongAI(*players[0], *players[1]);
}

void PongGame::exit() {
    Save();

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

    if (key == 't') {
        RunGeneration();
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

    CheckForTopPlayer(&(pong->GetPlayer1()));
    CheckForTopPlayer(&(pong->GetPlayer2()));

    if (pong != nullptr) {
        delete pong;
    }

    UpdateMatchGeneration();

    players[match * 2]->GetPaddle().SetPosition(0,
                PongAI::GetBoardHeight() / 2 - players[match * 2]->GetPaddle().GetHeight() / 2);
    players[match * 2 + 1]->GetPaddle().SetPosition(1240,
                PongAI::GetBoardHeight() / 2 - players[match * 2 + 1]->GetPaddle().GetHeight() / 2);


    pong = new PongAI(*players[match * 2], *players[match * 2 + 1]);
    pong->training = training;
    gamestate = TWOAI;
}

void PongGame::UpdateMatchGeneration() {
    match++;

    if (match == POPULATIONSIZE / 2) {
        match = 0;
        generation++;

        if (generation >= 10) {
            training = false;
        }

        vector<Player*> nextgen;
        for (int i = 0; i < topplayers.size(); ++i) {
            for (int j = 0; j < OFFSPRINGPERTOPPLAYER && nextgen.size() < POPULATIONSIZE; ++j) {
                nextgen.push_back(topplayers[i]->GenerateOffspring());
            }
        }

        for (Player* playerpointer : players) {
            if (playerpointer != nullptr) {
                delete playerpointer;
            }
        }
        players.clear();

        players = nextgen;
        nextgen.clear();
        topplayers.clear();

        for (int i = 0; i < POPULATIONSIZE / 5; ++i) {
            delete players[i];
            players[i] = new AI(0);
        }
        
        std::random_shuffle(players.begin(), players.end());
    }


}

void PongGame::RunGeneration() {
    int currentgeneration = generation;
    while (currentgeneration >= generation - 9) {
        pong->Update();
        CheckForWinner();
    }
}

void PongGame::Save() {
    for(int i = 0; i < POPULATIONSIZE; ++i) {
        std::string savefile = "models/" + std::to_string(i) + ".net";
        if (!players[i]->IsHuman()) {
            AI* ai = dynamic_cast<AI*>(players[i]);
            ai->GetNet().save(savefile);
        }
    }
}

void PongGame::CheckForTopPlayer(Player* player) {
    if (topplayers.size() < TOPPLAYERSIZE) {
        topplayers.push_back(player);
    }

    for (int i = 0; i < topplayers.size(); ++i) {
        if (player->GetHits() > topplayers[i]->GetHits()) {
            Player *tocheck  = topplayers[i];
            topplayers[i] = player;
            CheckForTopPlayer(tocheck);
        }
    }
}