#include "Network.h"
#include <stdexcept>
#include <sstream>

NeuralNetwork::NeuralNetwork() : numberOfInputs_(0), numberOfOutputs_(0) {}

NeuralNetwork::NeuralNetwork(int numberOfInputs, int numberOfOutputs) : numberOfInputs_(numberOfInputs), numberOfOutputs_(numberOfOutputs) {
    printf("Creating network with %d inputs and %d outputs\n", numberOfInputs, numberOfOutputs);
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

NeuralNetwork::NeuralNetwork(std::string data){
    std::vector<std::string> lines;
    std::string line;
    std::istringstream stream(data);
    while (std::getline(stream, line)) {
        lines.push_back(line);
    }

    if (lines.size() < 2) {
        throw std::invalid_argument("Invalid data format");
    }

    numberOfInputs_ = std::stoi(lines[0].substr(lines[0].find(":") + 1));
    numberOfOutputs_ = std::stoi(lines[1].substr(lines[1].find(":") + 1));

    std::string nodesIds = lines[2].substr(lines[2].find(":") + 1);
    std::vector<int> nodesIdsVector;
    std::istringstream nodesStream(nodesIds);
    std::string nodeId;
    while (std::getline(nodesStream, nodeId, ',')) {
        nodesIdsVector.push_back(std::stoi(nodeId));
    }

    for(int id : nodesIdsVector) {
        nodes_.push_back(new NN_Node(id));
    }

    for (long unsigned int i = 3; i < lines.size(); i++) {
        std::string line = lines[i];
        if (line.find("{") != std::string::npos) {
            int from = std::stoi(line.substr(line.find(":") + 1, line.find(" ")));
            int to = std::stoi(line.substr(line.find("To:") + 3, line.find(" ", line.find("To:") + 3)));
            double weight = std::stod(line.substr(line.find("Weight:") + 7, line.find("}")));
            addConnection(getNodeById(from), getNodeById(to), weight);
        }
    }

}

NeuralNetwork::~NeuralNetwork() {}

void NeuralNetwork::addNode() {
    nodes_.push_back(new NN_Node(getNextId()));
}

void NeuralNetwork::addConnection(NN_Node* from, NN_Node* to, double weight) {        //from ----> to input flows to output
    if(from == nullptr || to == nullptr) {
        throw std::invalid_argument("Node not found");
    }
    if(getNodeType(to->getId()) == NodeType::INPUT) {
        throw std::invalid_argument("Cannot connect to input node");
    }
    to->addInput(from, weight);

    for(NN_Node* node : nodes_) {
        node->clearCheckedNode();
    }
}

int NeuralNetwork::getNextId() {
    long unsigned int usedIds[nodes_.size()];
    for(long unsigned int i = 0; i < nodes_.size(); i++) {
        usedIds[i] = nodes_[i]->getId();
    }
    for(long unsigned int i = 0; i < nodes_.size(); i++) {
        bool found = false;
        for(long unsigned int j = 0; j < nodes_.size(); j++) {
            if(i == usedIds[j]) {
                found = true;
                break;
            }
        }
        if(!found) {
            return i;
        }
    }
    return nodes_.size();
}

NN_Node* NeuralNetwork::getNodeById(int id) {
    for(long unsigned int i = 0; i < nodes_.size(); i++) {
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

std::string NeuralNetwork::toString() {
    std::string str = "";
    str += "Number_of_inputs:" + std::to_string(numberOfInputs_) + "\n";
    str += "Number_of_outputs:" + std::to_string(numberOfOutputs_) + "\n";
    str += "Nodes:";
    for(NN_Node* node : nodes_) {
        str += std::to_string(node->getId()) + ",";
    }
    str += "\n";
    for(long unsigned int i = 0; i < nodes_.size(); i++) {
        if(!nodes_[i]->isEmpty()) {
            str += nodes_[i]->toString();            
        }
    }
    return str;
}

void NeuralNetwork::evolve() {
    addRandomConnections(.0025);

    networkCleaning();
}

void NeuralNetwork::addRandomConnections(double chance){
    for(int fromIDX = (int)nodes_.size()-1; fromIDX >= 0; fromIDX--) {
        for(int toIDX = (int)nodes_.size()-1; toIDX >= 0; toIDX--) {
            NN_Node* from = nodes_[fromIDX];
            NN_Node* to = nodes_[toIDX];
            //printf("Attempting %d -> %d\n", from->getId(), to->getId());
            if(from->isConnected(to) || getNodeType(to->getId()) == NodeType::INPUT) {
                continue;
            }
            if((rand() % 100)/100.0 < chance) {
                printf("adding connection from %d to %d\n", from->getId(), to->getId());
                addConnection(from, to, (rand() % 100)/100.0);
            }
        }
    }
}

void NeuralNetwork::RemoveNode(NN_Node* node) {
    for(NN_Node* n : nodes_) {
        n->removeInput(node);
    }
    for(long unsigned int i = 0; i < nodes_.size(); i++) {
        if(nodes_[i] == node) {
            nodes_.erase(nodes_.begin() + i);
            delete node;
            return;
        }
    }
}

void NeuralNetwork::networkCleaning() {
    for(int i = numberOfInputs_; i < numberOfInputs_ + numberOfOutputs_; i++) {
        nodes_[i]->getValue();
    }

    for(long unsigned int i = numberOfInputs_ + numberOfOutputs_; i < nodes_.size(); i++) {
        int val = nodes_[i]->getTouched();
        if(val == 0) {
            printf("Removed Node %d unused\n", nodes_[i]->getId());
            RemoveNode(nodes_[i]);
            i--;
        }
    }
}