#include "GeneralAI.h"

using namespace std;

GeneralAI::GeneralAI(int inputSize, int outputSize, int inputAmplitude, int outputAmplitude) :
    INPUT_SIZE(inputSize), OUTPUT_SIZE(outputSize), INPUT_AMPLITUDE(inputAmplitude), OUTPUT_AMPLITUDE(outputAmplitude)
{
    if(inputSize < 0)
    {
        throw out_of_range(string( "negative INPUT_SIZE" ));
    }

    if(outputSize < 0)
    {
        throw out_of_range(string( "negative OUTPUT_SIZE" ));
    }

    if(inputAmplitude < 0)
    {
        throw out_of_range(string( "negative INPUT_AMPLITUDE" ));
    }

    if(outputAmplitude < 0)
    {
        throw out_of_range(string( "negative OUTPUT_AMPLITUDE" ));
    }
}

GeneralAI::~GeneralAI()
{

}

void GeneralAI::learn(const vector<int>& input, const vector<int>& output, float outcome)
{
    if((int)input.size() != INPUT_SIZE)
    {
        throw length_error(string( "invalid input length" ));
    }
    else if((int)output.size() != OUTPUT_SIZE)
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
    if((int)input.size() != INPUT_SIZE)
    {
        throw invalid_argument(string( "Invalid input size" ));
    }

    vector<int> output = coreOutput(input);

    if((int)output.size() != OUTPUT_SIZE)
    {
        throw invalid_argument( string("Invalid output size") );
    }

    return output;
}
