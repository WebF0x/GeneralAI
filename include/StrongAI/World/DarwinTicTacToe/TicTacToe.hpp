#ifndef TIC_TAC_TOE_HPP
#define TIC_TAC_TOE_HPP

#include "StrongAI/AI/GeneralAI/GeneralAI.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>    //swap

class TicTacToe
{
    public:
        enum class Token { None, X, O };
        const double ILLEGAL_MOVE_WORTH = -1.f;
        const double LOST_GAME_WORTH = -.5f;
        const double TIE_GAME_WORTH = 0.f;
        const double WON_GAME_WORTH = 1.f;

        TicTacToe() {}
        virtual ~TicTacToe() {}

        /**
        *   Return winner( X or O ) of the match, or None if tie game.
        **/
        Token match( GeneralAI& player1, GeneralAI& player2 );

    private:
        /**
        *   Converts the player output to an integer in range [ 0, 8 ]
        **/
        int getPlayerMove( GeneralAI& player, const std::vector< double >& input );

        ///End game conditions
        bool isWinning( const std::vector< Token >& board, Token turn );
        bool boardIsFull( const std::vector< Token >& board );
        std::vector< double > boardToInput( const std::vector< Token >& board );
};

#endif // TIC_TAC_TOE_HPP
