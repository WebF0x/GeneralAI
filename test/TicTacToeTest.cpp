#include "UnitTest++/UnitTest++.h"
#include "World/TicTacToe/TicTacToe.hpp"

#include <stdexcept>
#include <vector>

int tokenCount( const TicTacToe::Board board )
{
    int count = 0;

    for( const auto& row : board )
    {
        for( const auto& token : row )
        {
            if( token != TicTacToe::Token::None )
            {
                count++;
            }
        }
    }

    return count;
}

bool isEmptyBoard( const TicTacToe::Board board )
{
    return tokenCount( board ) == 0;
}

SUITE( TicTacToeTest )
{
    TEST( defaultConstructorCreatesEmpty3X3Board )
    {
        TicTacToe game;
        const TicTacToe::Board board = game.getBoard();
        CHECK( isEmptyBoard( board ) );
    }

    TEST( setTokenAtCorrectPosition )
    {
        TicTacToe game;
        const auto token = TicTacToe::Token::X;
        const int x = 1;
        const int y = 2;

        game.setToken( token, x, y );
        const TicTacToe::Board board = game.getBoard();

        CHECK_EQUAL( 1, tokenCount( board ) );
        CHECK( board[x][y] == token );
    }

    TEST( setTokenThrowsExceptionIfPositionIsInvalid )
    {
        TicTacToe game;
        const auto token = TicTacToe::Token::X;

        CHECK_THROW( game.setToken( token, -1,  0 ), std::out_of_range );
        CHECK_THROW( game.setToken( token,  3,  0 ), std::out_of_range );
        CHECK_THROW( game.setToken( token,  0, -1 ), std::out_of_range );
        CHECK_THROW( game.setToken( token,  0,  3 ), std::out_of_range );
    }
}
