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
        std::vector<int> coreOutput(const std::vector<int>& input);
        void coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome);

        std::vector<int> getMemory() const;
        void setMemory(std::vector<int> memory);

        void visualizeInput(const std::vector<int>& input);
        char inputToChar(int input);
};

#endif // TICTACTOEHUMAN_H
