#include "AI/ExampleAI/ExampleAI.hpp"

ExampleAI::ExampleAI( int inputSize, int outputSize, int maxInput, int maxOutput )
    : GeneralAI( inputSize, outputSize, maxInput, maxOutput )
{
    // Constructor
}

void ExampleAI::coreLearn( const std::vector< double >& input, const std::vector< double >& output, double outcome )
{
    // Learn
}

std::vector< double > ExampleAI::coreOutput( const std::vector< double >& input )
{
    // Output
    std::vector< double > output( OUTPUT_SIZE );
    return output;
}
