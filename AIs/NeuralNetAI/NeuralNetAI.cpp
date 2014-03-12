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

vector<int> NeuralNetAI::getMemory() const
{
    /// Real memory
    vector<int> memory;

    memory.push_back(m_weights.size()); // Both dimensions of m_weights are equal: only need to save it once (Square Matrix)

    for(auto &row : m_weights)
    {
        for(auto weight : row)
        {
            weight * (float)numeric_limits<int>::max()
            memory.push_back(i);
        }
    }

    /// GeneralAI
    memory.push_back(INPUT_SIZE);
    memory.push_back(OUTPUT_SIZE);
    memory.push_back(INPUT_AMPLITUDE);
    memory.push_back(OUTPUT_AMPLITUDE);

    return memory;
}

void NeuralNetAI::setMemory(vector<int> memory)
{
    /// Parameter validation
    if(memory.size() < 4)
    {
        return;
    }

    /// GeneralAI
    int expectedValues[4] = {INPUT_SIZE, OUTPUT_SIZE, INPUT_AMPLITUDE, OUTPUT_AMPLITUDE};
    for(int i=0;i<4;++i)
    {
        if(memory.back() != expectedValues[3-i])
        {
            throw invalid_argument(string("bad memory format"));
        }
        memory.pop_back();
    }

    /// Layers and weights
    unsigned int memoryIndex = 0;

    const int NB_LAYERS = memory[memoryIndex++];
    m_weights = vector< vector<float> >(NB_LAYERS);

    for(auto &layer : m_weights)
    {
        const int LAYER_SIZE = memory[memoryIndex++];
        layer = vector<float>(LAYER_SIZE);

        for(int i=0; i<LAYER_SIZE; ++i)
        {
            layer[i] = memory[memoryIndex++];
        }
    }
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








