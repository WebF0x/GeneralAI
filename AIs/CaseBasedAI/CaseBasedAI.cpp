#include "CaseBasedAI.h"

using namespace std;

CaseBasedAI::CaseBasedAI(unsigned int inputSize, unsigned int outputSize, int maxInput, int maxOutput)
    : GeneralAI(inputSize, outputSize, maxInput, maxOutput)
{
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    randomGenerator = new default_random_engine(seed);

    /*
    //Was used for testing coreOutput()
    vector<int> v(inputSize);
    vector<int> v2(outputSize);
    v2[0] = 2;
    float outcome = 0.f;
    map<vector<int>, float> minimap;
    minimap[v2] = outcome;
    m_memory[v] = minimap;
    */
}

CaseBasedAI::~CaseBasedAI()
{
    delete randomGenerator;
}


vector<int> CaseBasedAI::coreOutput(const vector<int>& input) const
{
    map< vector<int>, map<vector<int>, float> > ::const_iterator  reactions = m_memory.find(input);

    ///Input NOT seen before
    if(reactions == m_memory.end())
    {
        //Try some new reaction
        return  randomOutput();   //[0,0,..,0]
    }

    ///Input seen before!
    //Find our best past reaction
    vector<int> output = reactions->second.begin()->first;
    float outcome =  reactions->second.begin()->second;
    //      Output    Outcome
    pair< vector<int>, float> bestPastReaction;
    bestPastReaction = make_pair(output, outcome);

    for (map<vector<int>, float>::const_iterator it=reactions->second.begin() /* +1 */; it!=reactions->second.end(); ++it)
    {
        if(it->second > bestPastReaction.second)   //Better outcome
        {
            bestPastReaction = make_pair (it->first, it->second);
        }
    }

    float randomNumber = randomProbability();
    if(bestPastReaction.second > randomNumber) //Best outcome greater than random number between 0 and 1
    {
        return bestPastReaction.first;  //Repeat this reaction
    }
    else
    {
        //Find a new reaction never tried before
        vector<int> reaction;

        do
        {
            reaction = randomOutput();
        }while(reactions->second.count(reaction));

        return reaction;

    }
}

void CaseBasedAI::coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome)
{

}

vector<int> CaseBasedAI::getMemory() const
{
    return vector<int> ();
}

void CaseBasedAI::setMemory(std::vector<int> memory)
{

}

vector<int> CaseBasedAI::randomOutput() const
{
    vector<int> output(OUTPUT_SIZE);
    uniform_int_distribution<int> distribution(-OUTPUT_AMPLITUDE,OUTPUT_AMPLITUDE);

    for(unsigned int i=0; i<OUTPUT_SIZE; ++i)
    {
        output[i] = distribution(*randomGenerator);  //Had to use pointers because this method is const. Can't modify the object RandomAI
    }

    return output;
}

float CaseBasedAI::randomProbability() const
{
    uniform_real_distribution<float> distribution(0, 1);
    return distribution(*randomGenerator);
}
