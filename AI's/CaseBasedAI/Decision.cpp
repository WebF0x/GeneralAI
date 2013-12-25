#include "Decision.h"

using namespace std;

Decision::Decision(const Situation& situation, const int reaction, const Result& result):
    m_situation(situation), m_reaction(reaction), m_result(result)
{

}

Decision Decision::decisionFromString(string data)
{
    ///Will store info on substrings
    string situationData, reactionData, resultData;

    ///Découper en substrings
    unsigned int i(0);
    for(i=0; i<data.length(); i++)
    {
        /// Trouver le caractère ';'
        if(data[i] == ';')
        {
            situationData = data.substr(0,i);
            i++;
            break;
        }
    }

    for(unsigned int j(i); j<data.length(); j++)
    {
        /// Trouver le 2e caractère ";"
        if(data[j] == ';')
        {
            reactionData = data.substr(i,j-i);
            j++;
            resultData = data.substr(j,data.length()-j-i);
            break;
        }
    }

    ///Générer les éléments d'une décision
    Situation tempSituation(Situation::fromString(situationData));

    stringstream ss;
    int tempReaction;
    ss<<reactionData;
    ss>>tempReaction;

    Result tempResult (resultFromString(resultData));

    return Decision(tempSituation, tempReaction, tempResult);
}

Result Decision::resultFromString(const string& str)
{
    if(str == "0")
        return Good;

    else if(str == "2")
        return Bad;

    else
        return Neutral;
}

Situation Decision::getSituation()  const             {return m_situation;}
void Decision::setSituation(const Situation& s) {m_situation = s;}

int Decision::getReaction() const                     {return m_reaction;}
void Decision::setReaction(const int r)   {m_reaction = r;}

Result Decision::getResult() const                    {return m_result;}
void Decision::setResult(const Result& r)       {m_result = r;}

Decision Decision::operator=(const Decision& decision)
{
    m_situation = decision.m_situation;
    m_reaction = decision.m_reaction;
    m_result = decision.m_result;

    return *this;
}

bool Decision::operator==(const Decision& decision) const
{
    return ((m_situation == decision.m_situation) &&
            (m_reaction == decision.m_reaction) &&
            (m_result == decision.m_result));
}

string Decision::toString() const
{
    stringstream ss;

    //Situation
    ss << m_situation.toString();
    ss << ";";

    //Reaction
    ss << m_reaction;
    ss << ";";

    //Result
    ss << m_result;


    return ss.str();
}












