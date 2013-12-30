/**
*   Warning: This file doesn't comply with the generalAI model!
**/

#include "CaseBasedAI.h"

using namespace std;

CaseBasedAI::CaseBasedAI(const std::vector<int>& possibleReactions) :
    m_possibleReactions(possibleReactions), m_lastDecision(NULL)
{

}

CaseBasedAI::~CaseBasedAI()
{
    for(unsigned int i(0); i<m_memory.size(); i++)
    {
        delete m_memory[i];
    }
    delete m_lastDecision;
}

void CaseBasedAI::makeDecision(const Decision& decision)
{
    delete m_lastDecision;
    m_lastDecision = new Decision(decision);
    memorizeDecision(decision);
}


void CaseBasedAI::makeDecision(const Situation& sit, int reaction, const Result& res)
{
    makeDecision(Decision(sit,reaction,res));
}

void CaseBasedAI::memorizeDecision(const Decision& decision)
{
    ///Vérifier si on se souvient d'une décision identique
    bool similarSituationExists = false;
    for(unsigned int i(0);i<m_memory.size(); i++)
    {
        ///Memoire de décision non-Bad: on la remplace
        if( (m_memory[i]->getSituation() == decision.getSituation()) &&
            (m_memory[i]->getReaction()  == decision.getReaction())  &&
            (m_memory[i]->getResult()    != Bad))
        {
            m_memory.erase(m_memory.begin() + i);
            m_memory.push_back(new Decision(decision));
        }

            similarSituationExists = similarSituationExists || ((m_memory[i]->getSituation() == decision.getSituation()) &&
                                                                (m_memory[i]->getReaction()  == decision.getReaction()));
    }

    if(!similarSituationExists)
    {
        m_memory.push_back(new Decision(decision));
    }

    clearDoubles();
}

void CaseBasedAI::clearDoubles()
{
    bool repeat;
    do
    {
        repeat = false;
        for(unsigned int i(0); i<m_memory.size(); i++)
        {
            for(unsigned int j(i+1); j<m_memory.size(); j++)
            {
                if( *m_memory[i] == *m_memory[j] )
                {
                    m_memory.erase(m_memory.begin() + j);
                    repeat = true;
                }

            }
        }
    }while (repeat);
}

void CaseBasedAI::forceDecision(const Decision& decision)
{
    makeDecision(decision);
}

int CaseBasedAI::getReaction(const Situation& currentSituation)
{
    ///Mimic good past Decisions
    std::vector<Decision*> goodPastDecisions     = getPastDecisions(currentSituation , Good);
    if (!goodPastDecisions.empty())
    {
        makeDecision(*goodPastDecisions[0]);
        return goodPastDecisions[0]->getReaction();
    }

    std::vector<Decision*> neutralPastDecisions  = getPastDecisions(currentSituation , Neutral);
    std::vector<Decision*> badPastDecisions      = getPastDecisions(currentSituation , Bad);

    /// Try a new reaction
    std::vector<Decision*> previousDecisions;
    previousDecisions.reserve(neutralPastDecisions.size() + badPastDecisions.size());
    previousDecisions.insert( previousDecisions.end(), neutralPastDecisions.begin(), neutralPastDecisions.end() );
    previousDecisions.insert( previousDecisions.end(), badPastDecisions.begin(), badPastDecisions.end() );

    int potentialReaction = newReaction(previousDecisions);
    if (potentialReaction != INVALID_REACTION)
    {
        makeDecision(currentSituation, potentialReaction, Neutral);
        return potentialReaction;
    }

    ///Try a neutral reaction
    if(!neutralPastDecisions.empty())
    {
        makeDecision(*neutralPastDecisions[0]);
        return neutralPastDecisions[0]->getReaction();
    }
    else
    ///All possible reactions are Bad
    ///     ===> The last decision was bad
    {
        punish();
        return INVALID_REACTION;
    }
}

void CaseBasedAI::learn(const Decision& decision)
{
    memorizeDecision(decision);
}

void CaseBasedAI::forget(const Decision& decision)
{
    for (unsigned int i(0); i<m_memory.size(); i++)
    {
        if(*m_memory[i] == decision)
        {
            m_memory.erase(m_memory.begin() + i);
            cout<<"Memoire effacee"<<endl;
            break;
        }
    }
}

void CaseBasedAI::reward()
{
    if (m_lastDecision != NULL)
    {
        m_lastDecision->setResult(Good);
        memorizeDecision(*m_lastDecision);
    }
}

void CaseBasedAI::punish()
{
    if (m_lastDecision != NULL)
    {
        m_lastDecision->setResult(Bad);
        memorizeDecision(*m_lastDecision);
    }
}

std::vector<Decision*> CaseBasedAI::getPastDecisions(const Situation& situation, Result resultWanted)
{
    std::vector<Decision*> decisionVector;
    for(unsigned int i(0); i<m_memory.size(); i++)
    {
        if( (m_memory[i]->getSituation() == situation) &&
            (m_memory[i]->getResult() == resultWanted))
        {
            decisionVector.push_back(m_memory[i]);
        }
    }
    return decisionVector;
}

int CaseBasedAI::newReaction(const std::vector<Decision*>& possibleDecisions)
{
    ///Try to find a new reaction
    for (unsigned int i(0); i<m_possibleReactions.size(); i++)
    {
        bool isNewReaction = true;
        for (unsigned int j(0); j<possibleDecisions.size(); j++)
        {
            if (possibleDecisions[j]->getReaction() == m_possibleReactions[i])
            {
                isNewReaction = false;
            }
        }

        if (isNewReaction)
        {
            return m_possibleReactions[i];
        }
    }
    return INVALID_REACTION;
}

bool CaseBasedAI::saveMemory(const string& fileName) const
{
    ///Open saveFile
    ofstream saveFile;
    saveFile.open(fileName.data());
    if (!saveFile.is_open())
        return false;

    ///Write memory in file
    for(unsigned int i(0); i<m_memory.size(); i++)
    {
        saveFile<<m_memory[i]->toString()<<endl;
    }

    saveFile.close();
    return true;
}

bool CaseBasedAI::loadMemory(const string& fileName)
{
    ///Open saveFile
    ifstream saveFile;
    saveFile.open(fileName.data());
    if(!saveFile.is_open())
    {
        cout<<"File does not exist!"<<endl;
        return false;
    }
    else
    {
        /// Recreate memory from file
        string saveData;
        while (getline(saveFile, saveData))
        {
            m_memory.push_back(new Decision(Decision::decisionFromString(saveData)));
        }

        saveFile.close();
        cout<<"Memory loaded"<<endl;
        return true;
    }
}



