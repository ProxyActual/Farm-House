#include "Network.h"
#include <stdexcept>

NeuralNetwork::NeuralNetwork(int numberOfInputs, int numberOfOutputs) : numberOfInputs_(numberOfInputs), numberOfOutputs_(numberOfOutputs) {
    if(numberOfInputs < 1 || numberOfOutputs < 1) {
        throw std::invalid_argument("Number of inputs and outputs must be greater than 0");
    }
    for(int i = 0; i < numberOfInputs; i++) {
        nodes_.push_back(new NN_Node(i));
    }
    for(int i = 0; i < numberOfOutputs; i++) {
        nodes_.push_back(new NN_Node(i + numberOfInputs));
    }
}

NeuralNetwork::~NeuralNetwork() {}

void NeuralNetwork::addNode() {
    nodes_.push_back(new NN_Node(getNextId()));
}

void NeuralNetwork::addConnection(int from, int to, double weight) {        //from ----> to input flows to output
    NN_Node* fromNode = getNodeById(from);
    NN_Node* toNode = getNodeById(to);
    if(fromNode == nullptr || toNode == nullptr) {
        throw std::invalid_argument("Node not found");
    }
    if(getNodeType(to) == NodeType::INPUT) {
        throw std::invalid_argument("Cannot connect to input node");
    }
    fromNode->addOutput(toNode);
    toNode->addInput(fromNode, weight);
}

int NeuralNetwork::getNextId() {
    int usedIds[nodes_.size()];
    for(int i = 0; i < nodes_.size(); i++) {
        usedIds[i] = nodes_[i]->getId();
    }
    for(int i = 0; i < nodes_.size(); i++) {
        bool found = false;
        for(int j = 0; j < nodes_.size(); j++) {
            if(i == usedIds[j]) {
                found = true;
                break;
            }
        }
        if(!found) {
            return i;
        }
    }
}

NN_Node* NeuralNetwork::getNodeById(int id) {
    for(int i = 0; i < nodes_.size(); i++) {
        if(nodes_[i]->getId() == id) {
            return nodes_[i];
        }
    }
    return nullptr;
}

NeuralNetwork::NodeType NeuralNetwork::getNodeType(int id) {
    if(id < numberOfInputs_) {
        return NodeType::INPUT;
    } else if(id < numberOfInputs_ + numberOfOutputs_) {
        return NodeType::OUTPUT;
    } else {
        return NodeType::MID;
    }
}
