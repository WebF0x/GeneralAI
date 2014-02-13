#ifndef GENERALAI_H
#define GENERALAI_H

#include "SaveSystem.h"
#include <iostream>
#include <stdexcept>
#include <tuple>

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
        *   Worst outcome: -1.f
        *   Best outcome :  1.f
        **/
        void learn(const std::vector<int>& input, const std::vector<int>& output, float outcome);
        void learn(const std::tuple<std::vector<int>, std::vector<int>, float>& lesson);
        void learn(float outcome);  /// Learn the outcome of the lastDecision

        std::pair < std::vector<int>, std::vector<int> >       lastDecision() const;
        std::tuple< std::vector<int>, std::vector<int>, float> lastLesson() const;
        void reset();

        bool validInput(const std::vector<int>& input) const;
        bool validOutput(const std::vector<int>& output) const;
        bool validOutcome(float outcome) const;

    private:
        /// Subclasses must implement these methods
        virtual void coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome) = 0;
        virtual std::vector<int> coreOutput(const std::vector<int>& input) = 0;

        /// Short-term memory
        std::pair<std::vector<int>,std::vector<int> > m_lastDecision;
        std::tuple<std::vector<int>, std::vector<int>, float> m_lastLesson;
        bool m_lastDecisionEnabled = false;
        bool m_lastLessonEnabled = false;


        bool validVector(const std::vector<int>& v, unsigned int size, int amplitude) const;
};

#endif // GENERALAI_H
