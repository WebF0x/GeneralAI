#ifndef CONSOLEHUMANAI_H
#define CONSOLEHUMANAI_H

#include "../GeneralAI/GeneralAI.h"
#include <iostream>
#include <String>

class ConsoleHumanAI : public GeneralAI
{
    public:
        virtual std::vector<int> getOutput(const std::vector<int>& input) const;
        virtual void learn(const std::vector<int>& input, const std::vector<int>& output, float outcome);

    protected:
        virtual std::vector<int> getMemory() const;
        virtual bool setMemory(std::vector<int> memory);

    private:
        void printVector(const std::vector<int>& vect) const;
};

#endif // CONSOLEHUMANAI_H
