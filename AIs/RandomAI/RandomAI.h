#ifndef RANDOMAI_H
#define RANDOMAI_H

#include "../GeneralAI/GeneralAI.h"

#include <chrono>   //To generate seed for randomGenerator
#include <random>   //To generate random values

class RandomAI : public GeneralAI
{
    public:
        RandomAI(unsigned int inputSize, unsigned int outputSize, int maxInput, int maxOutput);
        ~RandomAI();

    private:
        std::default_random_engine* randomGenerator;
        std::uniform_int_distribution<int>* distribution;

        virtual void coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome);
        virtual std::vector<int> coreOutput(const std::vector<int>& input) const;

        virtual std::vector<int> getMemory() const;
        virtual void setMemory(std::vector<int> memory);
};

#endif // RANDOMAI_H
