#include "UnitTest++/UnitTest++.h"
#include "World/TicTacToe/TicTacToe.hpp"

#include <vector>

bool isEmptyBoard( const TicTacToe::Board board )
{
    for( const auto& row : board )
    {
        for( const auto& token : row )
        {
            if( token != TicTacToe::Token::None )
            {
                return false;
            }
        }
    }

    return true;
}

SUITE( TicTacToeTest )
{
    TEST( defaultConstructorCreatesEmpty3X3Board )
    {
        TicTacToe game;
        const TicTacToe::Board board = game.getBoard();
        CHECK( isEmptyBoard( board ) );
    }
}
