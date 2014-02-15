#ifndef NEURALNETAI_H
#define NEURALNETAI_H

#include "../GeneralAI/GeneralAI.h"
#include <vector>
#include <chrono>
#include <random>

class NeuralNetAI : public GeneralAI
{
    public:
        NeuralNetAI(int inputSize, int outputSize, int maxInput, int maxOutput);
        virtual ~NeuralNetAI();

    private:
        virtual void coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome);
        virtual std::vector<int> coreOutput(const std::vector<int>& input);

        /// SaveSystem
        virtual std::vector<int> getMemory() const;
        virtual void setMemory(std::vector<int> memory);

        ///Random
        std::default_random_engine randomGenerator;
        float randomProbability();

        /// Network structure
        /**/std::vector< std::vector<int> > m_layers;   //Are weights integers, floats, etc.?
};

#endif // NEURALNETAI_H
