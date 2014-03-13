#include "NeuralNetAI.h"

using namespace std;

NeuralNetAI::NeuralNetAI(int inputSize, int outputSize, int maxInput, int maxOutput)
    : GeneralAI(inputSize, outputSize, maxInput, maxOutput)
{
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    randomGenerator = default_random_engine(seed);
}

NeuralNetAI::~NeuralNetAI()
{
}

void NeuralNetAI::coreLearn(const vector<int>& input, const vector<int>& output, float outcome)
{
    return;
}

vector<int> NeuralNetAI::coreOutput(const vector<int>& input)
{
    return vector<int>(OUTPUT_SIZE);
}

float NeuralNetAI::randomProbability()
{
    uniform_real_distribution<float> distribution(0, 1);
    return distribution(randomGenerator);
}

float NeuralNetAI::function(const float x)
{
    /// Function
    float y = coreFunction(x);

    /// Make sure y is valid
    if(y < -OUTPUT_AMPLITUDE)
    {
        return -OUTPUT_AMPLITUDE;
    }

    if(y > OUTPUT_AMPLITUDE)
    {
        return OUTPUT_AMPLITUDE;
    }

    return y;
}

float NeuralNetAI::coreFunction(const float x)
{
    /// Function
    return x;
}








