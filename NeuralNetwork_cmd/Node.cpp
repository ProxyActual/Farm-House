#include "Node.h"


NN_Node::NN_Node(int id) : id_(id), calculatedValue_(0xffffffffff) {}

NN_Node::~NN_Node() {}

void NN_Node::addInput(NN_Node* input, double weight) {
    if(input->hasConnectionTo(this)) {
        printf("Loop detected\n");
        return;
    }
    if(getNodeIndex(input) != -1) {
        int index = 0;
        for(long unsigned int i = 0; i < inputs_.size(); i++) {
            if(inputs_[i] == input) {
                index = i;
                break;
            }
        }
        inputWeights_[index] = weight + inputWeights_[index];
    }else{
        inputs_.push_back(input);
        inputWeights_.push_back(weight);
    }
}

int NN_Node::getId() const {
    return id_;
}

std::string NN_Node::toString() {
    std::string result = "";
    for(long unsigned int i = 0; i < inputs_.size(); i++) {
        result += "{From:" + std::to_string(inputs_[i]->getId()) + " To:" + std::to_string(getId()) + " Weight:" + std::to_string(inputWeights_[i]) + "}\n";
    }
    return result;
}

double NN_Node::getValue(){
    double result = 0;
    touched++;
    if(calculatedValue_ != 0xffffffffff) {
        return calculatedValue_;
    }
    for(long unsigned int i = 0; i < inputs_.size(); i++) {
        result += inputs_[i]->getValue() * inputWeights_[i];
    }
    calculatedValue_ = result;
    return result;
}

double NN_Node::getWeight(NN_Node* node) {
    int index = getNodeIndex(node);
    if(index != -1) {
        return inputWeights_[index];
    }
    return 0;
}

bool NN_Node::isConnected(NN_Node* node) {
    return getNodeIndex(node) != -1;
}

bool NN_Node::hasConnectionTo(NN_Node* TargetNodenode) {
    //printf("Checking for connection: from %d, To %d\n", getId(), TargetNodenode->getId());
    if(TargetNodenode == this) {
        return true;
    }
    if(CheckedNode) {
        return false;
    }
    for(long unsigned int i = 0; i < inputs_.size(); i++) {
        if(inputs_[i] == TargetNodenode) {
            return true;
        }
        if(inputs_[i]->hasConnectionTo(TargetNodenode)) {
            return true;
        }
    }
    CheckedNode = true;
    return false;
}

int NN_Node::getNodeIndex(NN_Node* node) {
    for(long unsigned int i = 0; i < inputs_.size(); i++) {
        if(inputs_[i] == node) {
            return i;
        }
    }
    return -1;
}

void NN_Node::removeInput(NN_Node* input) {
    int index = getNodeIndex(input);
    if(index != -1) {
        inputs_.erase(inputs_.begin() + index);
        inputWeights_.erase(inputWeights_.begin() + index);
    }
}