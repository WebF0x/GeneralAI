#include "AI.h"

using namespace std;

/**/#include <cstdlib>

AI::AI(const std::vector<int>& possibleReactions) :
    m_possibleReactions(possibleReactions), m_lastDecision(NULL)
{
}

AI::~AI()
{
    for(unsigned int i(0); i<m_memory2.size(); i++)
    {
        delete m_memory2[i];
    }
    delete m_lastDecision;
}

void AI::makeDecision(const Decision& decision)
{
    delete m_lastDecision;
    m_lastDecision = new Decision(decision);
    memorizeDecision(decision);
}


void AI::makeDecision(const Situation& sit, int reaction, const Result& res)
{
    makeDecision(Decision(sit,reaction,res));
}

void AI::memorizeDecision(const Decision& decision)
{
    ///Vérifier si on se souvient d'une décision identique
    bool similarSituationExists = false;
    for(unsigned int i(0);i<m_memory2.size(); i++)
    {
        ///Memoire de décision non-Bad: on la remplace
        if( (m_memory2[i]->getSituation() == decision.getSituation()) &&
            (m_memory2[i]->getReaction()  == decision.getReaction())  &&
            (m_memory2[i]->getResult()    != Bad))
        {
            m_memory2.erase(m_memory2.begin() + i);
            m_memory2.push_back(new Decision(decision));
        }

            similarSituationExists = similarSituationExists || ((m_memory2[i]->getSituation() == decision.getSituation()) &&
                                                                (m_memory2[i]->getReaction()  == decision.getReaction()));
    }

    if(!similarSituationExists)
    {
        m_memory2.push_back(new Decision(decision));
    }

    clearDoubles();
}

void AI::clearDoubles()
{
    bool repeat;
    do
    {
        repeat = false;
        for(unsigned int i(0); i<m_memory2.size(); i++)
        {
            for(unsigned int j(i+1); j<m_memory2.size(); j++)
            {
                if( *m_memory2[i] == *m_memory2[j] )
                {
                    m_memory2.erase(m_memory2.begin() + j);
                    repeat = true;
                }

            }
        }
    }while (repeat);
}

void AI::forceDecision(const Decision& decision)
{
    makeDecision(decision);
}

int AI::getReaction(const Situation& currentSituation)
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

void AI::learn(const Decision& decision)
{
    memorizeDecision(decision);
}

void AI::forget(const Decision& decision)
{
    for (unsigned int i(0); i<m_memory2.size(); i++)
    {
        if(*m_memory2[i] == decision)
        {
            m_memory2.erase(m_memory2.begin() + i);
            cout<<"Memoire effacee"<<endl;
            break;
        }
    }
}

void AI::reward()
{
    if (m_lastDecision != NULL)
    {
        m_lastDecision->setResult(Good);
        memorizeDecision(*m_lastDecision);
    }
}

void AI::punish()
{
    if (m_lastDecision != NULL)
    {
        m_lastDecision->setResult(Bad);
        memorizeDecision(*m_lastDecision);
    }
}

std::vector<Decision*> AI::getPastDecisions(const Situation& situation, Result resultWanted)
{
    std::vector<Decision*> decisionVector;
    for(unsigned int i(0); i<m_memory2.size(); i++)
    {
        if( (m_memory2[i]->getSituation() == situation) &&
            (m_memory2[i]->getResult() == resultWanted))
        {
            decisionVector.push_back(m_memory2[i]);
        }
    }
    return decisionVector;
}

int AI::newReaction(const std::vector<Decision*>& possibleDecisions)
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

bool AI::saveMemory(const string& fileName) const
{
    ///Open saveFile
    ofstream saveFile;
    saveFile.open(fileName.data());
    if (!saveFile.is_open())
        return false;

    ///Write memory in file
    for(unsigned int i(0); i<m_memory2.size(); i++)
    {
        saveFile<<m_memory2[i]->toString()<<endl;
    }

    saveFile.close();
    return true;
}

bool AI::loadMemory(const string& fileName)
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
            m_memory2.push_back(new Decision(Decision::decisionFromString(saveData)));
        }

        saveFile.close();
        cout<<"Memory loaded"<<endl;
        return true;
    }
}



