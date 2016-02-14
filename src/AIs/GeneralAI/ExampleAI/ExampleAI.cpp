#include "ExampleAI.h"

using namespace std;

ExampleAI::ExampleAI(int inputSize, int outputSize, int maxInput, int maxOutput)
    : GeneralAI(inputSize, outputSize, maxInput, maxOutput)
{
    //Constructor
}

void ExampleAI::coreLearn(const vector<float>& input, const vector<float>& output, float outcome)
{
    //Learn
}

vector<float> ExampleAI::coreOutput(const vector<float>& input)
{
    //Output
    vector<float> output(OUTPUT_SIZE);
    return output;
}
