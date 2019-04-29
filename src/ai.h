#pragma once


#include "player.h"
#include "floatfann.h"
#include "fann_cpp.h"
#include "pongai.h"
#include <random>
#include <time.h>

class AI: public Player {
private:
    Paddle paddle;
    const unsigned int num_input = 4;
    const unsigned int num_output = 3;
    const unsigned int num_layers = 5;
    const unsigned int num_neurons_hidden = 20;
    const float mutationstddev = 0.5;

    std::default_random_engine generator;

    FANN::neural_net net;
public:
    AI(const int startx);
    AI(const int startx, FANN::connection *connectionsarray);
    FANN::neural_net& GetNet();
    void Update(const Ball& ball);
    void SetDirection(const int toset){};
    Paddle& GetPaddle();
    AI* GenerateOffspring();
    bool IsHuman() const;
};