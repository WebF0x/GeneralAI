#include "CaseBasedAI.h"

using namespace std;

CaseBasedAI::CaseBasedAI(int inputSize, int outputSize, int maxInput, int maxOutput)
    : GeneralAI(inputSize, outputSize, maxInput, maxOutput)
{
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    randomGenerator = default_random_engine(seed);
}

CaseBasedAI::~CaseBasedAI()
{
}


vector<int> CaseBasedAI::coreOutput(const vector<int>& input)
{
    map< vector<int>, map<vector<int>, float> > ::const_iterator  situation = m_memory.find(input);

    ///Input NOT seen before
    if(situation == m_memory.end())
    {
        return  randomOutput();
    }

    ///Input seen before!
    vector<int> bestKnownOutput = bestOutput(situation->second);
    float bestKnownOutcome = (situation->second).at(bestKnownOutput);

    /**
        To prevent getting stuck in a local maximum:
        bestKnownOutput with the greatest outcome has the best chance to get picked.
        When not picked, returns a randomNewOutput
    **/
    float randomNumber = randomProbability();

    ///Either Repeat previous successful reaction
    if(bestKnownOutcome >= randomNumber)
    {
        return bestKnownOutput;
    }
    ///Or Try something new
    else
    {
        try
        {
            return randomNewOutput(situation->second);
        }
        //Not a single new output exists
        catch(runtime_error e)
        {
            //Last decision made must be worth either less than or equal to this bestKnownOutput
            learn(bestKnownOutcome);
            return bestKnownOutput;
        }
    }
}

void CaseBasedAI::coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome)
{
    ///Try to find input in memory
    map< vector<int>, map<vector<int>, float> > ::iterator  situation = m_memory.find(input);

    ///Input NOT seen before
    if(situation == m_memory.end())
    {
        map<vector<int>, float> newEntry;
        newEntry[output] = outcome;
        m_memory[input] = newEntry;
    }
    ///Input seen before
    else
    {
        map<vector<int>, float>::iterator reaction = situation->second.find(output);

        ///Output NOT seen before
        if(reaction == situation->second.end())
        {
            situation->second[output] = outcome;
        }
        ///Output seen before
        else
        {
            /*
            *   The outcome can only decrease.
            *   Why: Let's say we play we play chess. I make a move. My opponent could checkmate me but makes a mistake and doesn't and I win. I recall my move as a good move.
            *       The next time this situation presents itself, the opponent plays the checkmate and wins.
            *       The correct reaction is to forget the last time I was lucky and remember that my move can get me checkmated. Doing this move is as bad as losing.
            */
            if(outcome < situation->second[output])
            {
                situation->second[output] = outcome;
            }
        }
    }
}

vector<int> CaseBasedAI::randomOutput()
{
    vector<int> output(OUTPUT_SIZE);
    uniform_int_distribution<int> distribution(-OUTPUT_AMPLITUDE,OUTPUT_AMPLITUDE);

    for(int i=0; i<OUTPUT_SIZE; ++i)
    {
        output[i] = distribution(randomGenerator);
    }

    return output;
}

float CaseBasedAI::randomProbability()
{
    uniform_real_distribution<float> distribution(0, 1);
    return distribution(randomGenerator);
}

vector<int> CaseBasedAI::randomNewOutput(const map<vector<int>, float>& reactions)
{
    vector<int> output = randomOutput();
    if(!reactions.count(output))    ///output is a new reaction
    {
        return output;
    }

    ///output is NOT a new reaction
    vector<int> increasing = output;
    vector<int> decreasing = output;

    vector<int> minOutput(OUTPUT_SIZE, -OUTPUT_AMPLITUDE);  //e.g. [-5,-5,-5]
    vector<int> maxOutput(OUTPUT_SIZE, OUTPUT_AMPLITUDE);   //e.g. [ 5, 5, 5]

    /*
        Start at a random output and try everything by spreading towards the extrema
        Like this:
        ===*==
        ==*=*=
        =*===*
        *=====
        /////////////////////////////////////////////////////////////////////////////
        This algorithm works kind of like primary school paper arithmetic.
        It looks ugly, I'll refactor it later.
        Just trust me that it works, I tried it on paper!
    */
    while(decreasing!=minOutput || increasing!=maxOutput)  //As long as not everything has been tried
    {
        ///Increasing
        if(increasing!=maxOutput)
        {
            for(int i=0;i<OUTPUT_SIZE;++i)
            {
                if( increasing[i] < OUTPUT_AMPLITUDE)
                {
                    ++increasing[i];
                    break;
                }
                else
                {
                    increasing[i] = -OUTPUT_AMPLITUDE;
                }
            }

            if(!reactions.count(increasing))    //It is a new reaction
            {
                return increasing;
            }
        }

        ///Decreasing
        if(decreasing!=minOutput)
        {
            for(int i=0;i<OUTPUT_SIZE;++i)
            {
                if( decreasing[i] > -OUTPUT_AMPLITUDE)
                {
                    --decreasing[i];
                    break;
                }
                else
                {
                    decreasing[i] = OUTPUT_AMPLITUDE;
                }
            }

            if(!reactions.count(decreasing))    //It is a new reaction
            {
                return decreasing;
            }
        }
    }

    throw runtime_error(string("CaseBasedAI::randomNewOutput() no new output exist"));
}

vector<int> CaseBasedAI::bestOutput(const map<vector<int>, float>& reactions)
{
    if(reactions.empty())
    {
        throw length_error(string( " CaseBasedAI::bestOutput()'s parameter is empty" ));
    }

    vector< vector<int> > bestKnownOutputs;
    bestKnownOutputs.push_back(reactions.begin()->first);
    float bestKnownOutcome =  reactions.begin()->second;

    for (map<vector<int>, float>::const_iterator it=reactions.begin(); it!=reactions.end(); ++it)
    {
        const vector<int>& potentialOutput = it->first;
        float potentialOutcome = it->second;

        if(fabs(potentialOutcome - bestKnownOutcome) < .00000000001f)
        {
            bestKnownOutputs.push_back(potentialOutput);
        }
        else if(potentialOutcome > bestKnownOutcome)
        {
            bestKnownOutputs.clear();
            bestKnownOutputs.push_back(potentialOutput);
            bestKnownOutcome = potentialOutcome;
        }
    }

    ///Return one of the bestKnownOutputs at random
    uniform_int_distribution<int> distribution(0, bestKnownOutputs.size()-1);
    return bestKnownOutputs[distribution(randomGenerator)];
}

