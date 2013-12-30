#ifndef CASEBASEDAI_H
#define CASEBASEDAI_H

#include "../GeneralAI/GeneralAI.h"

/*
    To do: Base this class on CaseBasedAI, but it must comply with the generalAI model!
*/

class CaseBasedAI : public GeneralAI
{
    public:
        CaseBasedAI();
        virtual ~CaseBasedAI();

        virtual std::vector<int> getOutput(const std::vector<int>& input) const;
        virtual void learn(const std::vector<int>& input, const std::vector<int>& output, float outcome);

};

#endif // CASEBASEDAI_H
