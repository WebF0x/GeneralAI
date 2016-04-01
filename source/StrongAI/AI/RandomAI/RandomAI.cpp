#include "StrongAI/AI/RandomAI/RandomAI.hpp"

RandomAI::RandomAI( int inputSize, int outputSize, int maxInput, int maxOutput )
    : GeneralAI( inputSize, outputSize, maxInput, maxOutput )
{
}

void RandomAI::coreLearn( const std::vector< float >& input, const std::vector< float >& output, float outcome )
{
    // This AI is too dumb to learn anything!
}

std::vector< float > RandomAI::coreOutput( const std::vector< float >& input )
{
    return randomOutput();
}

std::vector< float > RandomAI::randomOutput()
{
    std::vector< float > output( OUTPUT_SIZE );
    std::uniform_real_distribution< float > distribution( -OUTPUT_AMPLITUDE, OUTPUT_AMPLITUDE );

    for( int i = 0; i < OUTPUT_SIZE; i++ )
    {
        output[ i ] = distribution( m_randomNumberGenerator );
    }

    return output;
}
