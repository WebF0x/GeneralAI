#pragma once

#include <vector>

class TicTacToe
{
    public:
        enum class Token { None, X, O };
        using Board = std::vector< std::vector< Token > >;

        TicTacToe();
        Board getBoard();
        void setToken( Token token, int x, int y );
        bool isLegalMove( int x, int y );

    private:
        Board m_board;

        static bool isInsideBoard( int x, int y);
};
