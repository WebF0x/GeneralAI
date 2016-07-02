#ifndef RANDOM_AI_HPP
#define RANDOM_AI_HPP

#include "AI/GeneralAI/GeneralAI.hpp"

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
