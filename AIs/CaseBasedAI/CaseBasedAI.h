#ifndef CASEBASEDAI_H
#define CASEBASEDAI_H

#include "../GeneralAI/GeneralAI.h"
#include <map>
#include <chrono>
#include <random>
#include <limits>   //numeric_limits<int>::max()

/*
    To do: Base this class on CaseBasedAI, but it must comply with the generalAI model!
*/

class CaseBasedAI : public GeneralAI
{
    public:
        CaseBasedAI(unsigned int inputSize, unsigned int outputSize, int maxInput, int maxOutput);
        virtual ~CaseBasedAI();

    private:
        virtual void coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome);
        virtual std::vector<int> coreOutput(const std::vector<int>& input) const;

        virtual std::vector<int> getMemory() const;
        virtual void setMemory(std::vector<int> memory);

        //             Input                     Output       Outcome
        std::map< std::vector<int>, std::map<std::vector<int>, float> > m_memory;

        std::default_random_engine* randomGenerator;
        float randomProbability() const;
        std::vector<int> randomOutput() const;


};

#endif // CASEBASEDAI_H
