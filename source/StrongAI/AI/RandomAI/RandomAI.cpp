#include "StrongAI/AI/RandomAI/RandomAI.hpp"
#include "Utility/Utility.hpp"

RandomAI::RandomAI( int inputSize, int outputSize, int maxInput, int maxOutput )
    : GeneralAI( inputSize, outputSize, maxInput, maxOutput )
{
}

void RandomAI::coreLearn( const std::vector< double >& input, const std::vector< double >& output, double outcome )
{
    // This AI is too dumb to learn anything!
}

std::vector< double > RandomAI::coreOutput( const std::vector< double >& input )
{
    return randomOutput();
}

std::vector< double > RandomAI::randomOutput()
{
    std::vector< double > output( OUTPUT_SIZE );
    std::uniform_real_distribution< double > distribution( -OUTPUT_AMPLITUDE, OUTPUT_AMPLITUDE );

    for( int i = 0; i < OUTPUT_SIZE; i++ )
    {
        output[ i ] = distribution( Random::getRandomNumberGenerator() );
    }

    return output;
}
