#ifndef RANDOM_AI_HPP
#define RANDOM_AI_HPP

#include "StrongAI/AI/GeneralAI/GeneralAI.hpp"
#include <chrono>   //To generate seed for randomGenerator
#include <random>   //To generate random values

class RandomAI : public GeneralAI
{
    public:
        RandomAI( int inputSize, int outputSize, int maxInput, int maxOutput );
        virtual ~RandomAI() {}

    private:
        std::vector< double > randomOutput();

        virtual void coreLearn( const std::vector< double >& input, const std::vector< double >& output, double outcome );
        virtual std::vector< double > coreOutput( const std::vector< double >& input );

        template < class Archive >
        void serialize( Archive & ar )
        {
            ar( cereal::virtual_base_class< GeneralAI >( this ) );
        }
};

#endif // RANDOM_AI_HPP
