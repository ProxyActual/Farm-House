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

        NeuralNetwork(int numberOfInputs, int numberOfOutputs);
        ~NeuralNetwork();

        void addNode();

        void addConnection(int from, int to, double weight);

        std::string toString();

    private:
        std::vector<NN_Node*> nodes_;

        int numberOfInputs_;
        int numberOfOutputs_;

        int getNextId();

        NN_Node* getNodeById(int id);

        NodeType getNodeType(int id);
};