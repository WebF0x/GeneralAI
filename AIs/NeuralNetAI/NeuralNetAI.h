#ifndef NEURALNETAI_H
#define NEURALNETAI_H

#include "../GeneralAI/GeneralAI.h"
#include <vector>
#include <map>
#include <chrono>

#include <cereal/types/vector.hpp>
#include <iostream>
#include <limits>
#include <random>   //Distributions

struct Node
{
    float value;
    std::map<int, float> incomingSynapses;  //incomingSynapses[source] = weight
};

class NeuralNetAI : public GeneralAI
{
public:
    NeuralNetAI(int inputSize, int outputSize, int maxInput, int maxOutput);

    void debug();

    void mutate();

public:
//private:
    ///GeneralAI
    virtual void coreLearn(const std::vector<float>& input, const std::vector<float>& output, float outcome);
    virtual std::vector<float> coreOutput(const std::vector<float>& input);

    ///Network
    void setSynapseWeight(int nodeIndex, int synapseIndex, float weight);
    void setNodeValue(int nodeIndex, float value);

    std::vector<Node> m_nodes; // [trigger, bias, inputs, outputs, neurons]

    void computeCycle();

    void resetNodesValues();
    void setInput(const std::vector<float>& input);

    bool triggered();

    float function(float x);
    virtual float coreFunction(float x);

    template <class Archive>
    void serialize( Archive & ar )
    {
        //ar(cereal::virtual_base_class<GeneralAI>( this ),m_nodes);
    }

    ///Constants
    const int INIT_NUMBER_OF_NEURONS=0;
    const int NUMBER_OF_NODES;
    const float INIT_NODE_VALUE = 0.f;
    const float INIT_WEIGHT_VALUE = 0.f;

    const int MAX_NUMBER_OF_CYCLES = 50;        //Prevent infinite loops in case the trigger node is never triggered
    const int MAX_NUMBER_OF_LEARN_CYCLES = 1000;  //Either successfully learn something or quit after trying this many times
    const float MAX_WEIGHT_VALUE;               //Prevent overflows and NaN bullshit
    const float MAX_NODE_VALUE;                 //Prevent overflows and NaN bullshit

    const float CHANCE_TO_MUTATE_ADD  = .5f;     //Probabilities related to a mutation
    const float CHANCE_TO_MUTATE_MUL  = .5f;     //Probabilities related to a mutation
    const float CHANCE_TO_MUTATE_KILL = .1f;   //Probabilities related to a mutation

    const float AMPLITUDE_ADD = 1.f; //Probabilities related to a mutation
    const float AMPLITUDE_MUL = 2.f; //Probabilities related to a mutation

    const float ACCEPTABLE_ERROR = .05f;  //Useless right now: the network doesn't learn()
};

#endif // NEURALNETAI_H
