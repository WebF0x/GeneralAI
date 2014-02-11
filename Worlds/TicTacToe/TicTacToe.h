#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "../../AIs/GeneralAI/GeneralAI.h"
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

class TicTacToe
{
    public:
        enum class Token {None, X, O};
        const float ILLEGAL_MOVE_WORTH = -1.f;
        const float LOST_GAME_WORTH = -.5f;
        const float TIE_GAME_WORTH = 0.f;
        const float WON_GAME_WORTH = 1.f;

        TicTacToe();
        virtual ~TicTacToe();

        /**
        *   Return winner(X,O) of the match, or None if tie game.
        **/
        Token match(GeneralAI& player1, GeneralAI& player2);



    private:
        std::default_random_engine randomGenerator;

        /**
        *   Converts the player output to an integer in range [0,8]
        **/
        int getPlayerMove(GeneralAI& player, const std::vector<int>& input);

        ///End game conditions
        bool isWinning(const std::vector<Token>& board, Token turn);
        bool boardIsFull(const std::vector<Token>& board);
};

#endif // TICTACTOE_H
