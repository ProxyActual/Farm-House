#include <iostream>

#include "Network.h"

int main(int argc, char* argv[]) {
    NeuralNetwork network_ = NeuralNetwork(10, 2);

    for(int i = 0; i < 4; i++) {
        network_.addNode();
    }

    network_.evolve();

    std::cout << network_.toString() << std::endl;

    NeuralNetwork network2_ = NeuralNetwork(network_.toString());

    std::cout << "updating elemnets\n\n" << std::endl;

    std::cout << network2_.toString() << std::endl;

    return 0; 
}