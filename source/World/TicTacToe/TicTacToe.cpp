#include "World/TicTacToe/TicTacToe.hpp"

#include <stdexcept>

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
    if( x<0 || y<0 || x>2 || y>2 )
    {
        throw std::out_of_range( "x and y must be between 0 and 2" );
    }

    m_board[x][y] = token;
}
