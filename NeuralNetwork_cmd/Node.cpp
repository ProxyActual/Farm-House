#include "Node.h"


NN_Node::NN_Node(int id) : id_(id), calculatedValue_(0xffffffffff) {}

NN_Node::~NN_Node() {}

void NN_Node::addInput(NN_Node* input, double weight) {
    inputs_.push_back(input);
    inputWeights_.push_back(weight);
}

void NN_Node::addOutput(NN_Node* output) {
    outputs_.push_back(output);
}

int NN_Node::getId() const {
    return id_;
}

std::string NN_Node::toString() {
    std::string result = "";
    for(int i = 0; i < inputs_.size(); i++) {
        result += "{From:" + std::to_string(inputs_[i]->getId()) + "To:" + std::to_string(getId()) + "Weight:" + std::to_string(inputWeights_[i]) + "}";
    }
    return result;
}

double NN_Node::getValue(){
    double result = 0;
    if(calculatedValue_ != 0xffffffffff) {
        return calculatedValue_;
    }
    for(int i = 0; i < inputs_.size(); i++) {
        result += inputs_[i]->getValue() * inputWeights_[i];
    }
    calculatedValue_ = result;
    return result;
}