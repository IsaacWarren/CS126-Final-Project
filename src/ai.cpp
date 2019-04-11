#include "ai.h"

AI::AI(const int startx): paddle(startx) {
    const unsigned int creator[] = { num_input, num_neurons_hidden, num_output};
    net.create_standard_array(num_layers, creator);
    net.set_activation_function_hidden(FANN::activation_function_enum::SIGMOID_SYMMETRIC);
    net.set_activation_function_output(FANN::activation_function_enum::SIGMOID_SYMMETRIC);
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

const Paddle& AI::GetPaddle() const {
    return paddle;
}