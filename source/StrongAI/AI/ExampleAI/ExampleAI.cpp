#include "StrongAI/AI/ExampleAI/ExampleAI.hpp"

ExampleAI::ExampleAI( int inputSize, int outputSize, int maxInput, int maxOutput )
    : GeneralAI( inputSize, outputSize, maxInput, maxOutput )
{
    // Constructor
}

void ExampleAI::coreLearn( const std::vector< float >& input, const std::vector< float >& output, float outcome )
{
    // Learn
}

std::vector< float > ExampleAI::coreOutput( const std::vector< float >& input )
{
    // Output
    std::vector< float > output( OUTPUT_SIZE );
    return output;
}
