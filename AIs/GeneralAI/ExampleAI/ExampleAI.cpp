#include "ExampleAI.h"

using namespace std;

ExampleAI::ExampleAI(int inputSize, int outputSize, int maxInput, int maxOutput)
    : GeneralAI(inputSize, outputSize, maxInput, maxOutput)
{
    //Constructor
}

void ExampleAI::coreLearn(const vector<int>& input, const vector<int>& output, float outcome)
{
    //Learn
}

vector<int> ExampleAI::coreOutput(const vector<int>& input)
{
    //Output
    vector<int> output(OUTPUT_SIZE);
    return output;
}
