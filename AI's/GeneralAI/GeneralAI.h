#ifndef GENERALAI_H
#define GENERALAI_H

#include "SaveSystem.h"
#include <vector>

/**
*   Abstract class for general artificial intelligence systems
*
*   -Basic methods
*   -Save/load system
**/
class GeneralAI : public SaveSystem
{
    public:
        virtual std::vector<int> getOutput(const std::vector<int>& input) = 0;

        /// Teach, for a given input, an output and its outcome
        /// Worst outcome: -1
        /// Best outcome:   1
        virtual void learn(const std::vector<int>& input, const std::vector<int>& output, float outcome) = 0;
};

#endif // GENERALAI_H
