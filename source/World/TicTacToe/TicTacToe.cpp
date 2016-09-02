#include "World/TicTacToe/TicTacToe.hpp"

#include <stdexcept>

TicTacToe::TicTacToe()
{
    const auto column = Board::value_type( 3, Token::None );
    m_board = Board( 3, column );
}

TicTacToe::Board TicTacToe::getBoard()
{
    return m_board;
}

void TicTacToe::setToken( Token token, int x, int y )
{
    if( !isInsideBoard(x,y) )
    {
        throw std::out_of_range( "x and y must be between 0 and 2" );
    }

    m_board[x][y] = token;
}

bool TicTacToe::isLegalMove( int x, int y )
{
    if( !isInsideBoard(x,y) )
    {
        return false;
    }

    if( m_board[x][y] != Token::None )
    {
        return false;
    }

    return true;
}

bool TicTacToe::isInsideBoard( int x, int y )
{
    return ( x>=0 && y>=0 && x<=2 && y<=2 );
}

TicTacToe::State TicTacToe::getState()
{
    if( isWinner( Token::X ) ) return State::VictoryX;
    if( isWinner( Token::O ) ) return State::VictoryO;
    if( isBoardFull() )        return State::TieGame;
    else                       return State::InProgress;
}

bool TicTacToe::isBoardFull()
{
    for( const auto& column : m_board )
    {
        for( const auto& token : column )
        {
            if(token==Token::None) return false;
        }
    }

    return true;
}

bool TicTacToe::isWinner( Token token )
{
    if( winColumnExists( token ) )   return true;
    if( winRowExists( token ) )      return true;
    if( winDiagonalExists( token ) ) return true;
    else                             return false;
}

bool TicTacToe::winColumnExists( Token token )
{
    for( int column=0; column<3; column++ )
    {
        bool isWinning = true;
        for( int row=0; row<3; row++ )
        {
            if( m_board[column][row] != token )
            {
                isWinning = false;
            }
        }

        if( isWinning ) return true;
    }

    return false;
}

bool TicTacToe::winRowExists( Token token )
{
    for( int row=0; row<3; row++ )
    {
        bool isWinning = true;
        for( int column=0; column<3; column++ )
        {
            if( m_board[column][row] != token )
            {
                isWinning = false;
            }
        }

        if( isWinning )
        {
            return true;
        }
    }

    return false;
}

bool TicTacToe::winDiagonalExists( Token token )
{
    if( m_board[0][0] == token &&
        m_board[1][1] == token &&
        m_board[2][2] == token )
    {
        return true;
    }

    if( m_board[2][0] == token &&
        m_board[1][1] == token &&
        m_board[0][2] == token )
    {
        return true;
    }

    return false;
}
