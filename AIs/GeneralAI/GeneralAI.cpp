#include "GeneralAI.h"
using namespace std;

GeneralAI::GeneralAI(unsigned int inputSize, unsigned int outputSize, int maxInput, int maxOutput) :
    m_inputSize(inputSize), m_outputSize(outputSize), m_maxInput(maxInput), m_maxOutput(maxOutput)
{
    if(maxInput < 0)
    {
        throw out_of_range( "negative maxInput" );
    }
    else if(maxOutput < 0)
    {
        throw out_of_range( "negative maxOutput" );
    }
}

void GeneralAI::learn(const vector<int>& input, const vector<int>& output, float outcome)
{
    if(input.size() != m_inputSize)
    {
        throw length_error( "invalid input length" );
    }
    else if(output.size() != m_outputSize)
    {
        throw length_error( "invalid output length" );
    }
    else if(0.f > outcome || outcome > 1.f)
    {
        throw out_of_range( "outcome not between 0 and 1" );
    }
    else
    {
        coreLearn(input, output, outcome);
    }
}

vector<int> GeneralAI::output(const vector<int>& input) const
{
    if(input.size() != m_inputSize)
    {
        throw invalid_argument( "Invalid input size" );
    }
    else
    {
        return coreOutput(input);
    }
}
