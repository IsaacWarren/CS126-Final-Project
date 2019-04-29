#include "ai.h"
#include <stdlib.h>

AI::AI(const int startx): paddle(startx) {
    const unsigned int creator[] = { num_input, num_neurons_hidden, num_neurons_hidden, num_neurons_hidden, num_output};
    net.create_standard_array(num_layers, creator);
    net.set_activation_function_hidden(FANN::activation_function_enum::SIGMOID_SYMMETRIC);
    net.set_activation_function_output(FANN::activation_function_enum::SIGMOID_SYMMETRIC);

    generator.seed(time(NULL));
}

AI::AI(const int startx, FANN::connection* connectionsarray): paddle(startx) {
    const unsigned int creator[] = {num_input, num_neurons_hidden, num_neurons_hidden, num_neurons_hidden, num_output};
    net.create_standard_array(num_layers, creator);
    net.set_activation_function_hidden(FANN::activation_function_enum::SIGMOID_SYMMETRIC);
    net.set_activation_function_output(FANN::activation_function_enum::SIGMOID_SYMMETRIC);
    net.set_weight_array(connectionsarray, net.get_total_connections());

    generator.seed(time(NULL));
}

void AI::Update(const Ball& ball) {
    fann_type inputarray[num_input];
    inputarray[0] = fabs(ball.GetPosition()[0] - paddle.GetPosition()[0]);
    inputarray[1] = ball.GetPosition()[1];
    inputarray[2] = paddle.GetPosition()[1];
    inputarray[3] = fabs(ball.GetSpeed()[0] / ball.GetSpeed()[1]);

    fann_type *outputarray;
    outputarray = net.run(inputarray);

    if (outputarray[0] > outputarray[1] && outputarray[0] > outputarray[2]) {
        paddle.MoveUp();
    } else if (outputarray[1] > outputarray[0] && outputarray[1] > outputarray[2]) {
        paddle.MoveDown();
    }
}

Paddle& AI::GetPaddle() {
    return paddle;
}

AI* AI::GenerateOffspring() {
    std::normal_distribution<float> distribution(0, mutationstddev);

    FANN::connection connectionsarray[net.get_total_connections()];
    net.get_connection_array(connectionsarray);
    for (unsigned int i = 0; i < net.get_total_connections(); ++i) {
        connectionsarray[i].weight += distribution(generator);
    }


    return new AI(paddle.GetPosition()[0], connectionsarray);
}

FANN::neural_net& AI::GetNet() {
    return net;
}

bool AI::IsHuman() const {
    return false;
}