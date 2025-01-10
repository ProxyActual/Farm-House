#pragma once

#include "Node.h"

#include <vector>
#include <string>

class NeuralNetwork{
    public:
        enum class NodeType {
            INPUT,
            OUTPUT,
            MID
        };

        NeuralNetwork();
        NeuralNetwork(int numberOfInputs, int numberOfOutputs);
        NeuralNetwork(std::string str);
        
        ~NeuralNetwork();

        void addNode();

        void addConnection(NN_Node* from, NN_Node* to, double weight);

        std::string toString();

        void evolve();

        NN_Node* getNodeById(int id);

    private:
        std::vector<NN_Node*> nodes_;

        int numberOfInputs_;
        int numberOfOutputs_;

        int getNextId();

        void RemoveNode(NN_Node* node);

        NodeType getNodeType(int id);

        void addRandomConnections(double chance);

        void networkCleaning();
};