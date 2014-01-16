#include "RandomAI.h"

using namespace std;

RandomAI::RandomAI(unsigned int inputSize, unsigned int outputSize, int maxInput, int maxOutput)
    : GeneralAI(inputSize, outputSize, maxInput, maxOutput)
{
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    randomGenerator = new default_random_engine(seed);
    distribution = new uniform_int_distribution<int>(-OUTPUT_AMPLITUDE,OUTPUT_AMPLITUDE);
}

RandomAI::~RandomAI()
{
    delete randomGenerator;
    delete distribution;
}

void RandomAI::coreLearn(const vector<int>& input, const vector<int>& output, float outcome)
{
    //This AI is too stupid to learn anything!
}

vector<int> RandomAI::coreOutput(const vector<int>& input) const
{
    vector<int> output(OUTPUT_SIZE);

    for(unsigned int i=0; i<OUTPUT_SIZE; ++i)
    {
        output[i] = (*distribution)(*randomGenerator);  //Had to use pointers because this method is const. Can't modify the object RandomAI
    }

    return output;
}


vector<int> RandomAI::getMemory() const
{
    //Too stupid to remember anything
    return vector<int>();
}

void RandomAI::setMemory(vector<int> memory)
{
    //Too stupid to remember anything
}






