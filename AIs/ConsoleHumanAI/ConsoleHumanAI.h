#ifndef CONSOLEHUMANAI_H
#define CONSOLEHUMANAI_H

#include "../GeneralAI/GeneralAI.h"
#include <iostream>
#include <String>

class ConsoleHumanAI : public GeneralAI
{
    public:
        ConsoleHumanAI(unsigned int inputSize, unsigned int outputSize, int maxInput, int maxOutput);

        virtual std::vector<int> coreOutput(const std::vector<int>& input) const;
        virtual void coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome);

    protected:
        virtual std::vector<int> getMemory() const;
        virtual void setMemory(std::vector<int> memory);

    private:
        void printVector(const std::vector<int>& vect) const;
};

#endif // CONSOLEHUMANAI_H
