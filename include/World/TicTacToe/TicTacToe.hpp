#pragma once

#include <vector>

class TicTacToe
{
    public:
        enum class State { InProgress, VictoryX, VictoryO, TieGame };
        enum class Token { None, X, O };
        using Board = std::vector< std::vector< Token > >;

        TicTacToe();
        Board getBoard();
        State getState();
        void setToken( Token token, int x, int y );
        bool isLegalMove( int x, int y );

    private:
        Board m_board;

        bool isBoardFull();
        bool isWinner( Token token );
        bool winColumnExists( Token token );
        bool winRowExists( Token token );
        bool winDiagonalExists( Token token );
        static bool isInsideBoard( int x, int y);
};
