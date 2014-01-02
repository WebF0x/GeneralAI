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
        GeneralAI(unsigned int inputSize, unsigned int outputSize, int maxInput, int maxOutput);

        /**
        *   Teach, for a given input, an output and its outcome
        *   Worst outcome: -1
        *   Best outcome:   1
        **/
        void learn(const std::vector<int>& input, const std::vector<int>& output, float outcome);

        /// Returns AI's output
        std::vector<int> output(const std::vector<int>& input) const;

    protected:
        ///Subclasses must implement these methods
        virtual void coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome) = 0;
        virtual std::vector<int> coreOutput(const std::vector<int>& input) const = 0;

    private:
        const unsigned int m_inputSize, m_outputSize;
        const int m_maxInput, m_maxOutput;
};

#endif // GENERALAI_H
