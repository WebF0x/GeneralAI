#ifndef GENERALAI_H
#define GENERALAI_H

#include "SaveSystem.h"
#include <iostream>
#include <stdexcept>

/**
*   Abstract class for general artificial intelligence systems
*
*   Public interface and core methods to be implemented by subclasses
*
*   Design pattern: Non-Virtual Interface
**/
class GeneralAI : public SaveSystem
{
    public:
        const int INPUT_SIZE, OUTPUT_SIZE, INPUT_AMPLITUDE, OUTPUT_AMPLITUDE;

        GeneralAI(int inputSize, int outputSize, int inputAmplitude, int outputAmplitude);
        virtual ~GeneralAI();

        /// Returns AI's output
        std::vector<int> output(const std::vector<int>& input);

        /**
        *   Learn the outcome of output(input)
        *
        *   Worst outcome: -1
        *   Best outcome :  1
        **/
        void learn(const std::vector<int>& input, const std::vector<int>& output, float outcome);

        /// Learn the outcome of the last output(input)
        void learn(float outcome);




    private:
        /// Subclasses must implement these methods
        virtual void coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome) = 0;
        virtual std::vector<int> coreOutput(const std::vector<int>& input) = 0;

        /// Short-term memory
        std::vector<int> m_lastInput, m_lastOutput;
};

#endif // GENERALAI_H
