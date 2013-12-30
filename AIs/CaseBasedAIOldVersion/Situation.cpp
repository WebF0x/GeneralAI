/**
*   Warning: This file doesn't comply with the generalAI model!
**/

#include "Situation.h"

using namespace std;

Situation::Situation(const vector<int>& variablesModel)
{
    m_variables = variablesModel;
}

Situation::Situation(const Situation& situationModel)
{
    m_variables = situationModel.m_variables;
}

Situation Situation::fromString(const string& data)
{
    vector<int> vInt;
    stringstream ss;
    ss<<data;

    for(unsigned int i(0); i < data.length(); i++)
    {
        int k;
        while(ss >>  k)
        {
            vInt.push_back(k);
        }
    }

    return Situation(vInt);
}

bool Situation::operator==(const Situation& situation2) const
{
    return (m_variables == situation2.m_variables);
}

Situation Situation::operator=(const Situation& situation2)
{
    m_variables = situation2.m_variables;
    return *this;
}

int Situation::size() const
{
    return m_variables.size();
}

string Situation::toString() const
{
    stringstream ss;

    for(unsigned int i(0); i<m_variables.size(); i++)
    {
        ss << m_variables[i];

        if(i != m_variables.size() - 1)
        {
            ss << " ";
        }
    }

    return ss.str();
}






