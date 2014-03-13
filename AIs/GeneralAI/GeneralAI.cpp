#include "GeneralAI.h"

using namespace std;

GeneralAI::GeneralAI(const int inputSize, const int outputSize, const int inputAmplitude, const int outputAmplitude) :
    INPUT_SIZE(inputSize), OUTPUT_SIZE(outputSize), INPUT_AMPLITUDE(inputAmplitude), OUTPUT_AMPLITUDE(outputAmplitude)
{
    if(INPUT_SIZE < 0)
    {
        throw out_of_range(string( "negative INPUT_SIZE" ));
    }

    if(OUTPUT_SIZE < 0)
    {
        throw out_of_range(string( "negative OUTPUT_SIZE" ));
    }

    if(INPUT_AMPLITUDE < 0)
    {
        throw out_of_range(string( "negative INPUT_AMPLITUDE" ));
    }

    if(OUTPUT_AMPLITUDE < 0)
    {
        throw out_of_range(string( "negative OUTPUT_AMPLITUDE" ));
    }
}

GeneralAI::~GeneralAI()
{
}

void GeneralAI::learn(const vector<int>& input, const vector<int>& output, const float outcome)
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

void GeneralAI::learn(const tuple< vector<int>, vector<int>, float>& lesson)
{
    learn(get<0>(lesson), get<1>(lesson), get<2>(lesson));
}

void GeneralAI::learn(const float outcome)
{
    if(m_lastDecisionEnabled) //m_lastInput and m_lastOutput are defined
    {
        learn(get<0>(m_lastDecision), get<1>(m_lastDecision), outcome);
    }
}

vector<int> GeneralAI::output(const vector<int>& input)
{
    ///Check parameters validity
    if(!validInput(input))
    {
        throw length_error(string( "invalid input" ));
    }

    vector<int> output = coreOutput(input);

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

pair< vector<int>, vector<int> > GeneralAI::lastDecision() const
{
    if(!m_lastDecisionEnabled)
    {
        throw logic_error(string("m_lastDecisionEnabled == false"));
    }

    return m_lastDecision;
}

tuple< vector<int>, vector<int>, float> GeneralAI::lastLesson() const
{
    if(!m_lastLessonEnabled)
    {
        throw logic_error(string("GeneralAI::m_lastLessonLearnedEnabled == false"));
    }

    return m_lastLesson;
}


bool GeneralAI::validVector(const vector<int>& v, const unsigned int size, const int amplitude)
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

bool GeneralAI::validInput(const vector<int>& input) const
{
    return validVector(input, (unsigned int)INPUT_SIZE, INPUT_AMPLITUDE);
}

bool GeneralAI::validOutput(const vector<int>& output) const
{
    return validVector(output, (unsigned int)OUTPUT_SIZE, OUTPUT_AMPLITUDE);
}

bool GeneralAI::validOutcome(const float outcome) const
{
    return (-1.f <= outcome && outcome <= 1.f);
}



