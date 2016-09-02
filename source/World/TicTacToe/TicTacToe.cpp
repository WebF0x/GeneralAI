#include "World/TicTacToe/TicTacToe.hpp"

TicTacToe::TicTacToe()
{
    const auto line = Board::value_type( 3, Token::None );
    m_board = Board( 3, line );
}

TicTacToe::Board TicTacToe::getBoard()
{
    return m_board;
}

void TicTacToe::setToken( Token token, int x, int y )
{
    m_board[x][y] = token;
}
