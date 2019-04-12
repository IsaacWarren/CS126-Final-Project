#include "ai.h"

AI::AI(const int startx): paddle(startx) {
    const unsigned int creator[] = { num_input, num_neurons_hidden, num_output};
    net.create_standard_array(num_layers, creator);
    net.set_activation_function_hidden(FANN::activation_function_enum::SIGMOID_SYMMETRIC);
    net.set_activation_function_output(FANN::activation_function_enum::SIGMOID_SYMMETRIC);
}

AI::AI(const int startx, FANN::neural_net nettoset): paddle(startx) {
    net = nettoset;
}

void AI::Update(const ofVec2f& ballposition) {
    fann_type inputarray[num_input];
    inputarray[0] = ballposition.x;
    inputarray[1] = ballposition.y;
    inputarray[2] = paddle.GetPosition().x;
    inputarray[3] = paddle.GetPosition().y;

    fann_type *outputarray;
    outputarray = net.run(inputarray);

    if (outputarray[0] > outputarray[1] && outputarray[0] > outputarray[2]) {
        paddle.MoveUp();
    } else if (outputarray[2] > outputarray[0] && outputarray[2] > outputarray[1]) {
        paddle.MoveDown();
    }
}

Paddle& AI::GetPaddle() {
    return paddle;
}

AI AI::GenerateOffspring() {
    std::default_random_engine generator;
    std::normal_distribution<float> distribution(0,0.1);

    FANN::connection connectionsarray[net.get_total_connections()];
    net.get_connection_array(connectionsarray);
    for (unsigned int i = 0; i < net.get_total_connections(); ++i) {
        connectionsarray[i].weight += distribution(generator);
    }

    const unsigned int creator[] = {num_input, num_neurons_hidden, num_output};
    FANN::neural_net offspring;
    offspring.create_standard_array(num_layers, creator);
    offspring.set_activation_function_hidden(FANN::activation_function_enum::SIGMOID_SYMMETRIC);
    offspring.set_activation_function_output(FANN::activation_function_enum::SIGMOID_SYMMETRIC);
    offspring.set_weight_array(connectionsarray, net.get_total_connections());
    return AI(paddle.GetPosition().x, offspring);
}