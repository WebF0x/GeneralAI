#include "StrongAI/AI/RandomAI/RandomAI.hpp"

using namespace std;

RandomAI::RandomAI( int inputSize, int outputSize, int maxInput, int maxOutput )
    : GeneralAI( inputSize, outputSize, maxInput, maxOutput )
{
}

void RandomAI::coreLearn( const vector< float >& input, const vector< float >& output, float outcome )
{
    // This AI is too dumb to learn anything!
}

vector< float > RandomAI::coreOutput( const vector< float >& input )
{
    return randomOutput();
}

vector< float > RandomAI::randomOutput()
{
    vector< float > output( OUTPUT_SIZE );
    uniform_real_distribution< float > distribution( -OUTPUT_AMPLITUDE, OUTPUT_AMPLITUDE );

    for( int i = 0; i < OUTPUT_SIZE; i++ )
    {
        output[ i ] = distribution( m_randomNumberGenerator );
    }

    return output;
}
