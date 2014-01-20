#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "../../AIs/CaseBasedAI/CaseBasedAI.h"
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

class TicTacToe
{
    public:
        TicTacToe();
        virtual ~TicTacToe();
        void match(GeneralAI* player1, GeneralAI* player2);

        static const int EMPTY = 0;
        static const int X = 1;
        static const int O = -1;


    protected:
        std::vector<int> board;
        int turn;
        bool gameOver;
        std::default_random_engine* randomGenerator;

        std::string squareStateToString(int);
        bool isWinning(int);
        void clearBoard();
        bool boardFull();
};

#endif // TICTACTOE_H
