#pragma once

#include "ofMain.h"
#include "player.h"
#include "floatfann.h"
#include "fann_cpp.h"
#include <random>

class AI: public Player {
private:
    Paddle paddle;
    const unsigned int num_input = 2;
    const unsigned int num_output = 3;
    const unsigned int num_layers = 5;
    const unsigned int num_neurons_hidden = 20;

    FANN::neural_net net;
public:
    AI(const int startx);
    AI(const int startx, FANN::connection *connectionsarray);
    void SetNet(const FANN::neural_net nettoset);
    void Update(const ofVec2f& ballposition);
    void SetDirection(const int toset){};
    Paddle& GetPaddle();
    AI* GenerateOffspring();
};