#pragma once

#include "ofMain.h"
#include "player.h"
#include "floatfann.h"
#include "fann_cpp.h"

class AI {
private:
    Paddle paddle;
    const unsigned int num_input = 4;
    const unsigned int num_output = 3;
    const unsigned int num_layers = 3;
    const unsigned int num_neurons_hidden = 8;

    unique_ptr<FANN::neural_net> net;
public:
    AI(const int startx);
    void Update();
    AI GenerateOffspring();
};