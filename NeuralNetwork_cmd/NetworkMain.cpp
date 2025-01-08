#include <iostream>

#include "Network.h"

int main(int argc, char* argv[]) {
    NeuralNetwork network_ = NeuralNetwork(2, 1);
    network_.addConnection(0, 2, 0.5);
    std::cout << network_.toString() << std::endl;
    return 0; 
}