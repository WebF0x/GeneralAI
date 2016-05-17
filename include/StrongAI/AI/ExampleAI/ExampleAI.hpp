#ifndef EXAMPLE_AI_HPP
#define EXAMPLE_AI_HPP

#include "StrongAI/AI/GeneralAI/GeneralAI.hpp"

class ExampleAI : public GeneralAI
{
    public:
        ExampleAI( int inputSize, int outputSize, int maxInput, int maxOutput );

    private:
        std::vector< double > coreOutput( const std::vector< double >& input );
        void coreLearn( const std::vector< double >& input, const std::vector< double >& output, double outcome );

        friend cereal::access;
        template < class Archive >
        void serialize( Archive & ar )
        {
            ar( cereal::virtual_base_class< GeneralAI >( this ) );

            /**
                You can serialize any variables that you want like this:
                    ar( cereal::virtual_base_class< GeneralAI >( this ), var1, var2, varN );
            **/
        }


};

#endif // EXAMPLE_AI_HPP
