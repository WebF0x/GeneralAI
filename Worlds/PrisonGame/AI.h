#ifndef AI_H
#define AI_H

#include <vector>
#include "Decision.h"
#include <iostream>
#include <fstream>
#include <string>

#define INVALID_REACTION (-1)

class AI
{
public:
    AI(const std::vector<int>& possibleReactions);
    virtual ~AI();

    int getReaction(const Situation&);
    void forceDecision(const Decision&);

    void learn(const Decision&);
    void forget(const Decision&);

    void reward();
    void punish();

    bool saveMemory(const std::string&) ;
    bool loadMemory(const std::string&);

private:
    /**
        On veut utiliser des pointeurs de décisions au lieu de copier les décisions au complet.
        Gain d'efficacité et meilleure gestion de la mémoire
    */
    std::vector<Decision*> m_memory2;

    std::vector<int> m_possibleReactions;
    Decision *m_lastDecision;

    void makeDecision(const Decision&);
    void makeDecision(const Situation&, int, const Result&);
    void clearDoubles();
    void memorizeDecision(const Decision&);
    std::vector<Decision*> getPastDecisions(const Situation& situation, Result resultWanted);
    int newReaction(const std::vector<Decision*>& possibleDecisions);
};

#endif // AI_H
