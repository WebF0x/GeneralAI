#ifndef NEURAL_NET_AI_HPP
#define NEURAL_NET_AI_HPP

#include "StrongAI/AI/GeneralAI/GeneralAI.hpp"
#include <map>
#include <vector>
#include <chrono>
#include <random>   //Distributions
#include <limits>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>

struct Node
{
    double value;
    std::map< int, double > incomingSynapses;  //incomingSynapses[ source ] = weight

    template < class Archive >
    void serialize( Archive & archive )
    {
        archive( value, incomingSynapses );
    }
};

class NeuralNetAI : public GeneralAI
{
public:
    NeuralNetAI() : GeneralAI(0, 0, 0, 0),
                    NUMBER_OF_NODES( 0 ),
                    MAX_WEIGHT_VALUE( 0 ),
                    MAX_NODE_VALUE( 0 )
    {
    }
    NeuralNetAI( int inputSize, int outputSize, int maxInput, int maxOutput );

    void debug();

    void mutate();

private:
    ///GeneralAI
    virtual void coreLearn( const std::vector< double >& input, const std::vector< double >& output, double outcome );
    virtual std::vector< double > coreOutput( const std::vector< double >& input );

    ///Network
    void setSynapseWeight( int nodeIndex, int synapseIndex, double weight );
    void setNodeValue( int nodeIndex, double value );

    std::vector< Node > m_nodes; // [ trigger, bias, inputs, outputs, neurons ]

    void computeCycle();

    void resetNodesValues();
    void setInput( const std::vector< double >& input );

    bool triggered();

    double function( double x );
    virtual double coreFunction( double x );

    bool almostEqual( const std::vector< double >& left, const std::vector< double >& right, double epsilon ) const;
    bool almostEqual( double left, double right, double epsilon ) const;

    ///Constants
    const int INIT_NUMBER_OF_NEURONS = 0;
    const int NUMBER_OF_NODES;
    const double INIT_NODE_VALUE = 0.f;
    const double INIT_WEIGHT_VALUE = 0.f;

    const int MAX_NUMBER_OF_CYCLES = 5;        //Prevent infinite loops in case the trigger node is never triggered
    const int MAX_NUMBER_OF_LEARN_CYCLES = 10;  //Either successfully learn something or quit after trying this many times
    const double MAX_WEIGHT_VALUE;               //Prevent overflows and NaN bullshit
    const double MAX_NODE_VALUE;                 //Prevent overflows and NaN bullshit

    const double CHANCE_TO_MUTATE_ADD  = .5f;     //Probabilities related to a mutation
    const double CHANCE_TO_MUTATE_MUL  = .5f;     //Probabilities related to a mutation
    const double CHANCE_TO_MUTATE_KILL = .1f;   //Probabilities related to a mutation

    const double AMPLITUDE_ADD = 1.f; //Probabilities related to a mutation
    const double AMPLITUDE_MUL = 2.f; //Probabilities related to a mutation

    const double ACCEPTABLE_ERROR = .1f;  //Useless right now: the network doesn't learn()

    //Serialization
    friend cereal::access;
    template < class Archive >
    void serialize( Archive & ar )
    {
        ar( cereal::make_nvp( "GeneralAI",cereal::virtual_base_class< GeneralAI >( this ) ) );
        ar( cereal::make_nvp( "Nodes",    m_nodes ) );
    }
};

#endif // NEURAL_NET_AI_HPP
