#ifndef TICTACTOEHUMAN_H
#define TICTACTOEHUMAN_H

#include "../../AIs/HumanAI/HumanAI.h"
#include "TicTacToe.h"

#include <iostream>
#include <vector>

class TicTacToeHuman : public HumanAI
{
    public:
        TicTacToeHuman(int inputSize, int outputSize, int maxInput, int maxOutput);

    private:
        std::vector<float> coreOutput(const std::vector<float>& input);
        void coreLearn(const std::vector<float>& input, const std::vector<float>& output, float outcome){}

        void visualizeInput(const std::vector<float>& input);
        char inputToChar(float input);
};

#endif // TICTACTOEHUMAN_H
