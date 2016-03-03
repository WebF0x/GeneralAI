#include "StrongAI/AI/GeneralAI/GeneralAI.hpp"

using namespace std;

//To do: Seed the random number generator with a random_device when it's implemented (*wink wink GCC*)
mt19937_64 GeneralAI::m_randomNumberGenerator(time(NULL));  //Shared random number generator

GeneralAI::GeneralAI(const int inputSize, const int outputSize, const int inputAmplitude, const int outputAmplitude) :
    INPUT_SIZE(inputSize), OUTPUT_SIZE(outputSize), INPUT_AMPLITUDE(inputAmplitude), OUTPUT_AMPLITUDE(outputAmplitude)
{
    if(INPUT_SIZE < 0)  throw out_of_range(string( "negative INPUT_SIZE" ));
    if(OUTPUT_SIZE < 0) throw out_of_range(string( "negative OUTPUT_SIZE" ));
    if(INPUT_AMPLITUDE < 0) throw out_of_range(string( "negative INPUT_AMPLITUDE" ));
    if(OUTPUT_AMPLITUDE < 0)throw out_of_range(string( "negative OUTPUT_AMPLITUDE" ));
}

void GeneralAI::learn(const vector<float>& input, const vector<float>& output, const float outcome)
{
    ///Check parameters validity
    if(!validInput(input))
    {
        throw length_error(string( "invalid input" ));
    }

    if(!validOutput(output))
    {
        throw length_error(string( "invalid output" ));
    }

    if(!validOutcome(outcome))
    {
        throw length_error(string( "invalid outcome" ));
    }

    ///Learn lesson
    coreLearn(input, output, outcome);

    ///Short-term memory
    m_lastLesson = make_tuple(input,output,outcome);
    m_lastLessonEnabled = true;
}

void GeneralAI::learn(const tuple< vector<float>, vector<float>, float>& lesson)
{
    auto& input = get<0>(lesson);
    auto& output = get<1>(lesson);
    auto& outcome = get<2>(lesson);

    learn(input, output, outcome);
}

void GeneralAI::learn(const pair<vector<float>,vector<float>>& decision, float outcome)
{
    auto& input = decision.first;
    auto& output = decision.second;

    learn(input, output, outcome);
}

void GeneralAI::learn(const float outcome)
{
    if(m_lastDecisionEnabled) //m_lastDecision is not undefined
    {
        learn(m_lastDecision, outcome);
    }
}

vector<float> GeneralAI::output(const vector<float>& input)
{
    ///Check parameters validity
    if(!validInput(input))
    {
        throw length_error(string( "invalid input" ));
    }

    vector<float> output = coreOutput(input);

    if(!validOutput(output))
    {
        throw length_error(string( "invalid output" ));
    }

    /// Remember the last decision made
    m_lastDecision = make_pair(input, output);
    m_lastDecisionEnabled = true;

    return output;
}

void GeneralAI::reset()
{
    m_lastDecisionEnabled = false;
}

pair< vector<float>, vector<float> > GeneralAI::lastDecision() const
{
    if(!m_lastDecisionEnabled)
    {
        throw logic_error(string("m_lastDecisionEnabled == false"));
    }

    return m_lastDecision;
}

tuple< vector<float>, vector<float>, float> GeneralAI::lastLesson() const
{
    if(!m_lastLessonEnabled)
    {
        throw logic_error(string("GeneralAI::m_lastLessonLearnedEnabled == false"));
    }

    return m_lastLesson;
}

bool GeneralAI::validVector(const vector<float>& v, const unsigned int size, const int amplitude)
{
    if(v.size() != size)
    {
        return false;
    }

    for(unsigned int i=0; i<v.size(); ++i)
    {
        if(!(-amplitude <= v[i] && v[i] <= amplitude))
        {
            return false;
        }
    }

    return true;
}

bool GeneralAI::validInput(const vector<float>& input) const
{
    return validVector(input, (unsigned int)INPUT_SIZE, INPUT_AMPLITUDE);
}

bool GeneralAI::validOutput(const vector<float>& output) const
{
    return validVector(output, (unsigned int)OUTPUT_SIZE, OUTPUT_AMPLITUDE);
}

bool GeneralAI::validOutcome(const float outcome) const
{
    return (-1.f <= outcome && outcome <= 1.f);
}

/**
*   Returns a random float in [0,1]
**/
float GeneralAI::randomProbability()
{
    uniform_real_distribution<float> distribution(0, 1);
    return distribution(m_randomNumberGenerator);
}


