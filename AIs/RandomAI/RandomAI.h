#ifndef RANDOMAI_H
#define RANDOMAI_H

#include "../GeneralAI/GeneralAI.h"

#include <chrono>   //To generate seed for randomGenerator
#include <random>   //To generate random values

class RandomAI : public GeneralAI
{
    public:
        RandomAI(int inputSize, int outputSize, int maxInput, int maxOutput);
        virtual ~RandomAI();

    private:
        std::default_random_engine randomGenerator;
        std::vector<int> randomOutput();

        virtual void coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome);
        virtual std::vector<int> coreOutput(const std::vector<int>& input);

        template <class Archive>
        void serialize( Archive & ar )
        {
            ar(cereal::virtual_base_class<GeneralAI>( this ));
        }
};

#endif // RANDOMAI_H
