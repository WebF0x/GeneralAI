#ifndef HUMANAI_H
#define HUMANAI_H

#include "../GeneralAI/GeneralAI.h"
#include <iostream>
#include <String>

class HumanAI : public GeneralAI
{
    public:
        HumanAI(int inputSize, int outputSize, int maxInput, int maxOutput);

    protected:
        virtual std::vector<int> getMemory() const;
        virtual void setMemory(std::vector<int> memory);

    private:
        virtual std::vector<int> coreOutput(const std::vector<int>& input) ;
        virtual void coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome);
        virtual void visualizeInput(const std::vector<int>& input);

        void printVector(const std::vector<int>& vect) const;

};

#endif // HUMANAI_H
