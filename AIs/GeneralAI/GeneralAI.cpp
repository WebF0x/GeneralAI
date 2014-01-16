#include "GeneralAI.h"

using namespace std;

GeneralAI::GeneralAI(unsigned int inputSize, unsigned int outputSize, int maxInput, int maxOutput) :
    INPUT_SIZE(inputSize), OUTPUT_SIZE(outputSize), INPUT_AMPLITUDE(maxInput), OUTPUT_AMPLITUDE(maxOutput)
{
    if(maxInput < 0)
    {
        throw out_of_range(string( "negative maxInput" ));
    }
    else if(maxOutput < 0)
    {
        throw out_of_range(string( "negative maxOutput" ));
    }
}

GeneralAI::~GeneralAI()
{

}

void GeneralAI::learn(const vector<int>& input, const vector<int>& output, float outcome)
{
    if(input.size() != INPUT_SIZE)
    {
        throw length_error(string( "invalid input length" ));
    }
    else if(output.size() != OUTPUT_SIZE)
    {
        throw length_error( string("invalid output length" ));
    }
    else if(-1.f > outcome || outcome > 1.f)
    {
        throw out_of_range( string("outcome not between -1 and 1" ));
    }
    else
    {
        coreLearn(input, output, outcome);
    }
}

vector<int> GeneralAI::output(const vector<int>& input) const
{
    if(input.size() != INPUT_SIZE)
    {
        throw invalid_argument(string( "Invalid input size" ));
    }

    vector<int> output = coreOutput(input);

    if(output.size() != OUTPUT_SIZE)
    {
        throw invalid_argument( string("Invalid output size") );
    }

    return output;
}
