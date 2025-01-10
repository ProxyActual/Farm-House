#pragma once

#include <vector>
#include <string>

class NN_Node
{
    public:
        NN_Node(int id);
        ~NN_Node();

        void addInput(NN_Node* input, double weight);

        void removeInput(NN_Node* input);

        int getId() const;

        double getValue();

        void setValue(double value) {
            calculatedValue_ = value;
        }

        bool isEmpty() {
            return inputs_.empty();
        }

        void clearCheckedNode() {
            CheckedNode = false;
        }

        int getTouched() {
            int val_touched = touched;
            touched = 0;
            return val_touched;
        }

        bool isConnected(NN_Node* node);

        double getWeight(NN_Node* node);

        NN_Node* getInputNode(int index){
            return inputs_[index];
        }

        std::string toString();

    private:
        int id_;
        int touched = 0;
        
        bool CheckedNode = false;

        std::vector<NN_Node*> inputs_;
        std::vector<double> inputWeights_;

        int getNodeIndex(NN_Node* node);
        bool hasConnectionTo(NN_Node* node);

        double calculatedValue_;
};