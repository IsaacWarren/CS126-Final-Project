#include "ponggame.h"



void PongGame::setup() {
    ofSetWindowTitle("Pong");
    ofBackground(0,0,0);
    for (int i = 0; i < POPULATIONSIZE; i++) {
        if (i % 2 == 0) {
            players.push_back(new AI(PLAYER1X));
        } else {
            players.push_back(new AI(PLAYER2X));
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

    if (gamestate == FASTTRAIN) {
        RunGeneration();
    }

    if (gamestate == TWOHUMAN) {
        pong->Update();
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

    if (gamestate == FASTTRAIN) {
        DrawTwoAI();
    }

    if (gamestate == MENU) {
        DrawMenu();
    }

}

void PongGame::keyPressed(int key) {
    if (key == 'r' && gamestate == TWOHUMAN || gamestate == MIXED) {
        ResetWithHuman();
    }

    if (key == 'm') {
        gamestate = MENU;
    }

    if (key == 't') {
        gamestate = TWOAI;
    }

    if (key == 'h') {
        gamestate = TWOHUMAN;
        ResetWithHuman();
    }

    if (key == 's' && gamestate == TWOAI) {
        Save();
    }

    if (key == 'l') {
        Load();
    }

    if (key == 'w') {
        pong->GetPlayer1().SetDirection(1);
    }
    if (key == 's' && gamestate != TWOAI) {
        pong->GetPlayer1().SetDirection(-1);
    }
    if (key == OF_KEY_UP) {
        pong->GetPlayer2().SetDirection(1);
    }
    if (key == OF_KEY_DOWN) {
        pong->GetPlayer2().SetDirection(-1);
    }

    if (key == 'q' && gamestate == TWOAI) {
        gamestate = FASTTRAIN;
    } else if (key == 'q' && gamestate == FASTTRAIN) {
        gamestate = TWOAI;
    }

}

void PongGame::keyReleased(int key) {
    if (key == OF_KEY_UP || key == OF_KEY_DOWN) {
        pong->GetPlayer2().SetDirection(0);
    }
    if (key == 'w' || key == 's' && gamestate != TWOAI) {
        pong->GetPlayer1().SetDirection(0);
    }
}

bool PongGame::CheckForWinner() {
    if (pong->IsWinner()) {
        ResetTwoAI();
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
        ofDrawBitmapString("Player1 won press R to ResetTwoAI", PongAI::GetBoardWidth() / 2 - 100, 100);
    } else {
        ofDrawBitmapString("Player2 won press R to ResetTwoAI", PongAI::GetBoardWidth() / 2 - 100, 100);
    }
}

void PongGame::DrawTwoAI() {
    ofSetColor(255,255,255);
    std::string matchstring = "Match: " + std::to_string(match);
    std::string generationstring = "Generation: " + std::to_string(generation);
    ofDrawBitmapString(matchstring, PongAI::GetBoardWidth() / 2 - 100, 100);
    ofDrawBitmapString(generationstring, PongAI::GetBoardWidth() / 2 - 100, 120);
    ofDrawBitmapString("Press q to toggle quick training", PongAI::GetBoardWidth() / 2 - 150, 140);
}

void PongGame::DrawMenu() {
    ofDrawBitmapString("Press t to train, press a to play an ai, press h for two human players and press m to get back to this menu",
                    PongAI::GetBoardWidth() / 2 - 400, 100);
    ofDrawBitmapString("Press s to save the models training and press l to load models from the models file",
                    PongAI::GetBoardWidth() / 2 - 300, 120);
}

void PongGame::ResetTwoAI() {

    CheckForTopPlayer(&(pong->GetPlayer1()));
    CheckForTopPlayer(&(pong->GetPlayer2()));

    if (pong != nullptr) {
        delete pong;
    }

    UpdateMatchGeneration();

    players[match * 2]->GetPaddle().SetPosition(PLAYER1X,
                PongAI::GetBoardHeight() / 2 - players[match * 2]->GetPaddle().GetHeight() / 2);
    players[match * 2 + 1]->GetPaddle().SetPosition(PLAYER2X,
                PongAI::GetBoardHeight() / 2 - players[match * 2 + 1]->GetPaddle().GetHeight() / 2);


    pong = new PongAI(*players[match * 2], *players[match * 2 + 1]);
    pong->solidwall = solidwall;
}

void PongGame::ResetWithHuman() {
    if (gamestate == TWOHUMAN) {
        delete pong;

        human1->GetPaddle().SetPosition(PLAYER1X,
                PongAI::GetBoardHeight() / 2 - players[match * 2]->GetPaddle().GetHeight() / 2);
        human2->GetPaddle().SetPosition(PLAYER2X,
                PongAI::GetBoardHeight() / 2 - players[match * 2 + 1]->GetPaddle().GetHeight() / 2);
        pong = new PongAI(*human1, *human2);
    }
}

void PongGame::UpdateMatchGeneration() {
    match++;

    if (match == POPULATIONSIZE / 2) {
        match = 0;
        generation++;

        if (generation >= SOLIDWALLGENERATIONS) {
            solidwall = false;
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

        for (int i = 0; i < NEWPLAYERS; ++i) {
            delete players[i];
            players[i] = new AI(0);
        }
        
        std::random_shuffle(players.begin(), players.end());
    }


}

void PongGame::RunGeneration() {
    int currentgeneration = generation;
    while (currentgeneration >= generation) {
        pong->Update();
        CheckForWinner();
    }
}

void PongGame::Save() {
    for (int i = 0; i < POPULATIONSIZE; ++i) {
        std::string savefile = "models/" + std::to_string(i) + ".net";
        if (!players[i]->IsHuman()) {
            AI* ai = dynamic_cast<AI*>(players[i]);
            ai->GetNet().save(savefile);
        }
    }
}

void PongGame::Load() {
    for (Player *playerptr : players) {
        delete playerptr;
    }

    for (int i  = 0; i < POPULATIONSIZE; ++i) {
        std::string loadfilestring = "models/" + std::to_string(i) + ".net";
        std::ifstream loadfilestream(loadfilestring);
        if (loadfilestream.good()) {
            loadfilestream.close();

            FANN::neural_net net;
            net.create_from_file(loadfilestring);
            FANN::connection connectionsarray[net.get_total_connections()];
            net.get_connection_array(connectionsarray);

            players[i] = new AI(0, connectionsarray);
        } else {
            loadfilestream.close();
            players[i] = new AI(0);
        }
    }

    ResetTwoAI();
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