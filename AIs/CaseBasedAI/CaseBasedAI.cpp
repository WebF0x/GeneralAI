#include "CaseBasedAI.h"

using namespace std;

CaseBasedAI::CaseBasedAI(unsigned int inputSize, unsigned int outputSize, int maxInput, int maxOutput)
    : GeneralAI(inputSize, outputSize, maxInput, maxOutput)
{
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    randomGenerator = new default_random_engine(seed);
}

CaseBasedAI::~CaseBasedAI()
{
    delete randomGenerator;
}


vector<int> CaseBasedAI::coreOutput(const vector<int>& input) const
{
    map< vector<int>, map<vector<int>, float> > ::const_iterator  situation = m_memory.find(input);

    ///Input NOT seen before
    if(situation == m_memory.end())
    {
        return  randomOutput();
    }

    ///Input seen before!
    //Find our best past reaction
    vector<int> output = situation->second.begin()->first;
    float outcome =  situation->second.begin()->second;
    //      Output    Outcome
    pair< vector<int>, float> bestPastReaction;
    bestPastReaction = make_pair(output, outcome);

    for (map<vector<int>, float>::const_iterator it=situation->second.begin(); it!=situation->second.end(); ++it)
    {
        if(it->second > bestPastReaction.second)   //Better outcome
        {
            bestPastReaction = make_pair (it->first, it->second);
        }
    }

    /*
        To prevent getting stuck in a local maximum:

    */
    float randomNumber = randomProbability();


    ///Repeat previous successful reaction
    if(bestPastReaction.second > randomNumber) //Best outcome greater than random number between 0 and 1
    {
        return bestPastReaction.first;  //Repeat this reaction
    }

    ///Try something new
    vector<int> reaction;
    do
    {
        reaction = randomOutput();
    }while(situation->second.count(reaction));

    return reaction;
}

void CaseBasedAI::coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome)
{
    //Try to find input in memory
    map< vector<int>, map<vector<int>, float> > ::iterator  situation = m_memory.find(input);

    ///Input NOT seen before
    if(situation == m_memory.end())
    {
        map<vector<int>, float> newEntry;
        newEntry[output] = outcome;
        m_memory[input] = newEntry;
        return;
    }
    ///Input seen before
    else
    {
        map<vector<int>, float>::iterator reaction = situation->second.find(output);

        ///Output NOT seen before
        if(reaction == situation->second.end())
        {
            situation->second[output] = outcome;
            return;
        }
        ///Output seen before
        else
        {
            float newOutcome = situation->second[output];
            newOutcome += outcome;

            if(newOutcome < -1.f)
            {
                newOutcome = -1.f;
            }
            else if(newOutcome > 1.f)
            {
                newOutcome = 1.f;
            }

            situation->second[output] = newOutcome;
            return;
        }
    }
}

vector<int> CaseBasedAI::getMemory() const
{
    vector<int> memory;

    ///Real memories
    for ( map< vector<int>, map<vector<int>, float> >::const_iterator itMem=m_memory.begin(); itMem!=m_memory.end(); ++itMem)
    {
        const vector<int> input = itMem->first;
        const map<vector<int>, float> reactions = itMem->second;

        //Push input
        for(unsigned int i=0; i<INPUT_SIZE; ++i)
        {
            memory.push_back(input[i]);
        }

        //Push size of reactions map
        memory.push_back(reactions.size());

        //Push reactions
        for (  map<vector<int>, float>::const_iterator itReaction=reactions.begin(); itReaction!=reactions.end(); ++itReaction)
        {
            vector<int> output = itReaction->first;
            float outcome = itReaction->second;

            //Push output
            for(unsigned int i=0; i<OUTPUT_SIZE; ++i)
            {
                memory.push_back(output[i]);
            }

            //Push outcome
            memory.push_back(outcome * numeric_limits<int>::max()); //Fraction of the maximum int value
        }
    }

    ///Save format
    memory.push_back(INPUT_SIZE);
    memory.push_back(OUTPUT_SIZE);
    memory.push_back(INPUT_AMPLITUDE);
    memory.push_back(OUTPUT_AMPLITUDE);

    return memory;
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
