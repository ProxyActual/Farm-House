#pragma once

#include <vector>
#include <string>

class NN_Node
{
    public:
        NN_Node(int id);
        ~NN_Node();

        void addInput(NN_Node* input, double weight);
        void addOutput(NN_Node* output);

        int getId() const;

        double getValue();

        void setValue(double value) {
            calculatedValue_ = value;
        }

        bool isEmpty() {
            return inputs_.empty();
        }

        bool isConnected(NN_Node* node);

        std::string toString();

    private:
        int id_;
        std::vector<NN_Node*> inputs_;
        std::vector<double> inputWeights_;
        std::vector<NN_Node*> outputs_;

        double calculatedValue_;
};