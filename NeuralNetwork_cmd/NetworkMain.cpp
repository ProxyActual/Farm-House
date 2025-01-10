#include <iostream>

#include "Network.h"
#include <fstream>
#include <sstream>

NeuralNetwork network_;

bool evolveNetwork = false;
bool NetworkCreated = false;

std::string validCommands[]= {
    "--newNN",
    "--loadNN",
    "--help",
    "--evolve"
};

std::string validCommandsHelp[] = {
    "<numberOfInputs> <numberOfOutputs> <numberOfMid>: Create a new neural network with the specified number of inputs and outputs",
    "<file>: Load a neural network from a file",
    "Print this help message",
    "Randomly add and manipulate connections in the network"
};

enum class Command {
    NEW_NN = 0,
    LOAD_NN,
    HELP,
    EVOLVE,
    INVALID
};

void printHelp(){
    std::cout << "Valid commands:" << std::endl;
    for(long unsigned int i = 0; i < sizeof(validCommands) / sizeof(validCommands[0]); i++){
        std::cout << validCommands[i] << " " << validCommandsHelp[i] << std::endl;
    }
}

bool makeNetworkFromFile(std::string filename){
    std::string fileData = "";
    std::ifstream inFile(filename);
    if (inFile) {
        std::ostringstream ss;
        ss << inFile.rdbuf();
        fileData = ss.str();
        inFile.close();
    } else {
        std::cout << "Failed to open file" << std::endl;
        return false;
    }
    network_ = NeuralNetwork(fileData);
    std::cout << "Loaded neural network from file" << std::endl;
    NetworkCreated = true;
    return true;
}

bool parseCommand(int argc, char* argv[]){
    if(argc <= 2){
        printHelp();
        return false;
    }
    for(int i = 1; i < argc; i++){
        if(std::string(argv[i]) == validCommands[static_cast<int>(Command::NEW_NN)]){
            if(i + 3 >= argc){
                std::cout << "Invalid number of arguments" << std::endl;
                return false;
            }
            if(NetworkCreated){
                std::cout << "Network already created" << std::endl;
                return false;
            }
            i++;
            int numberOfInputs = std::stoi(argv[i]);
            i++;
            int numberOfOutputs = std::stoi(argv[i]);
            i++;
            int numberOfMid = std::stoi(argv[i]);
            network_ = NeuralNetwork(numberOfInputs, numberOfOutputs);
            for(int i = 0; i < numberOfMid; i++){
                network_.addNode();
            }
            std::cout << "Created new neural network" << std::endl;
            NetworkCreated = true;
        }

        else if(std::string(argv[i]) == validCommands[static_cast<int>(Command::HELP)]){
            printHelp();
            return false;
        }

        else if(std::string(argv[i]) == validCommands[static_cast<int>(Command::EVOLVE)]){
            evolveNetwork = true;
            std::cout << "Evolve network" << std::endl;
        }

        else if(std::string(argv[i]) == validCommands[static_cast<int>(Command::LOAD_NN)]){
            if(i + 1 >= argc){
                std::cout << "Invalid number of arguments" << std::endl;
                return false;
            }
            i++;
            std::string file = argv[i];
            if(NetworkCreated){
                std::cout << "Network already created" << std::endl;
                return false;
            }
            if(!makeNetworkFromFile(file)){
                return false;
            }
        }

        else{
            std::cout << "Invalid command" << std::endl;
            printHelp();
            return false;
        }
    }
    return true;
}

void saveNetwork(){
    std::ofstream outFile("network.txt");
    if (outFile) {
        outFile << network_.toString();
        outFile.close();
    } else {
        std::cout << "Failed to save network" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if(!parseCommand(argc, argv)){
        return 1;
    }

    if(evolveNetwork){
        network_.evolve();
    }

    saveNetwork();

    return 0; 
}

