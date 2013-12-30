/**
*   Warning: This file doesn't comply with the generalAI model!
**/

#ifndef CASEBASEDAI_H
#define CASEBASEDAI_H

#include <vector>
#include "Decision.h"
#include <iostream>
#include <fstream>
#include <string>

#define INVALID_REACTION (-1)

class CaseBasedAI
{
    public:
        CaseBasedAI(const std::vector<int>& possibleReactions);
        virtual ~CaseBasedAI();

        int getReaction(const Situation&);
        void forceDecision(const Decision&);

        void learn(const Decision&);
        void forget(const Decision&);

        void reward();
        void punish();

        bool saveMemory(const std::string&) const ;
        bool loadMemory(const std::string&);

    private:
        /**
            On veut utiliser des pointeurs de décisions au lieu de copier les décisions au complet.
            Gain d'efficacité et meilleure gestion de la mémoire
        */
        std::vector<Decision*> m_memory;

        std::vector<int> m_possibleReactions;
        Decision *m_lastDecision;

        void makeDecision(const Decision&);
        void makeDecision(const Situation&, int, const Result&);
        void clearDoubles();
        void memorizeDecision(const Decision&);
        std::vector<Decision*> getPastDecisions(const Situation& situation, Result resultWanted);
        int newReaction(const std::vector<Decision*>& possibleDecisions);
};

#endif // CASEBASEDAI_H
