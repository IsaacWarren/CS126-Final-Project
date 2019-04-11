#include "ai.h"

AI::AI(const int startx): paddle(startx) {
    net = std::make_unique<FANN::neural_net>(FANN::neural_net());
    net->create_standard(num_layers, num_input, num_neurons_hidden, num_output);
    net->set_activation_function_hidden(FANN::activation_function_enum::SIGMOID_SYMMETRIC);
    net->set_activation_function_output(FANN::activation_function_enum::SIGMOID_SYMMETRIC);
}