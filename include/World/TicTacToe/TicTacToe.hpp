#pragma once

#include <vector>

class TicTacToe
{
    public:
        enum class Token { None, X, O };
        using Board = std::vector< std::vector< Token > >;

        TicTacToe();
        Board getBoard();

    private:
        Board m_board;
};
