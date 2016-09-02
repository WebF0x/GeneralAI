#include "UnitTest++/UnitTest++.h"
#include "World/TicTacToe/TicTacToe.hpp"

#include <stdexcept>
#include <vector>

int tokenCount( const TicTacToe::Board board )
{
    int count = 0;

    for( const auto& column : board )
    {
        for( const auto& token : column )
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

    TEST( placingTokenAtLegalPositionShouldWork )
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

    TEST( placingTokenOutsideBoardThrowsOutOfRangeException )
    {
        TicTacToe game;
        const auto token = TicTacToe::Token::X;

        CHECK_THROW( game.setToken( token, -1,  0 ), std::out_of_range );
        CHECK_THROW( game.setToken( token,  3,  0 ), std::out_of_range );
        CHECK_THROW( game.setToken( token,  0, -1 ), std::out_of_range );
        CHECK_THROW( game.setToken( token,  0,  3 ), std::out_of_range );
    }

    TEST( recognizeLegalMoveOnEmptySpace )
    {
        TicTacToe game;
        game.setToken( TicTacToe::Token::X, 0, 0 );
        CHECK( game.isLegalMove(2,2) );
    }

    TEST( recognizeIllegalMoveOnOccupiedSpace )
    {
        TicTacToe game;
        game.setToken( TicTacToe::Token::X, 0, 0 );
        CHECK( !game.isLegalMove(0,0) );
    }

    TEST( recognizeIllegalMoveIfOutsideBoard )
    {
        TicTacToe game;
        game.setToken( TicTacToe::Token::X, 0, 0 );
        CHECK( !game.isLegalMove(-1,  0) );
        CHECK( !game.isLegalMove( 3,  0) );
        CHECK( !game.isLegalMove( 0, -1) );
        CHECK( !game.isLegalMove( 0,  3) );
    }

    TEST( whenGameIsNotOverStateIsInProgress )
    {
        TicTacToe game;

        CHECK( game.getState() == TicTacToe::State::InProgress );
        game.setToken( TicTacToe::Token::X, 0, 0 );
        CHECK( game.getState() == TicTacToe::State::InProgress );
    }

    TEST( whenBoardIsFullAndNobodyWonStateIsTieGame )
    {
        TicTacToe game;

        game.setToken( TicTacToe::Token::X, 0, 0 );
        game.setToken( TicTacToe::Token::O, 0, 1 );
        game.setToken( TicTacToe::Token::X, 0, 2 );
        game.setToken( TicTacToe::Token::O, 2, 0 );
        game.setToken( TicTacToe::Token::X, 2, 1 );
        game.setToken( TicTacToe::Token::O, 2, 2 );
        game.setToken( TicTacToe::Token::X, 1, 0 );
        game.setToken( TicTacToe::Token::O, 1, 1 );
        game.setToken( TicTacToe::Token::X, 1, 2 );

        CHECK( game.getState() == TicTacToe::State::TieGame );
    }

    TEST( whenRowIsFullOfTheSameTokenStateIsVictoryOfPlayer )
    {
        TicTacToe game;

        game.setToken( TicTacToe::Token::X, 0, 0 );
        game.setToken( TicTacToe::Token::X, 1, 0 );
        game.setToken( TicTacToe::Token::X, 2, 0 );
        CHECK( game.getState() == TicTacToe::State::VictoryX );

        game.setToken( TicTacToe::Token::O, 0, 0 );
        game.setToken( TicTacToe::Token::O, 1, 0 );
        game.setToken( TicTacToe::Token::O, 2, 0 );
        CHECK( game.getState() == TicTacToe::State::VictoryO );
    }

    TEST( whenColumnIsFullOfTheSameTokenStateIsVictoryOfPlayer )
    {
        TicTacToe game;

        game.setToken( TicTacToe::Token::X, 0, 0 );
        game.setToken( TicTacToe::Token::X, 0, 1 );
        game.setToken( TicTacToe::Token::X, 0, 2 );
        CHECK( game.getState() == TicTacToe::State::VictoryX );

        game.setToken( TicTacToe::Token::O, 0, 0 );
        game.setToken( TicTacToe::Token::O, 0, 1 );
        game.setToken( TicTacToe::Token::O, 0, 2);
        CHECK( game.getState() == TicTacToe::State::VictoryO );
    }

    TEST( whenDiagonalIsFullOfTheSameTokenStateIsVictoryOfPlayer )
    {
        TicTacToe game;

        // Test first diagonal
        game.setToken( TicTacToe::Token::X, 0, 0 );
        game.setToken( TicTacToe::Token::X, 1, 1 );
        game.setToken( TicTacToe::Token::X, 2, 2 );
        CHECK( game.getState() == TicTacToe::State::VictoryX );

        game.setToken( TicTacToe::Token::O, 0, 0 );
        game.setToken( TicTacToe::Token::O, 1, 1 );
        game.setToken( TicTacToe::Token::O, 2, 2);
        CHECK( game.getState() == TicTacToe::State::VictoryO );

        // Reset the board
        game.setToken( TicTacToe::Token::None, 0, 0 );
        game.setToken( TicTacToe::Token::None, 1, 1 );
        game.setToken( TicTacToe::Token::None, 2, 2);

        // Test second diagonal
        game.setToken( TicTacToe::Token::X, 2, 0 );
        game.setToken( TicTacToe::Token::X, 1, 1 );
        game.setToken( TicTacToe::Token::X, 0, 2 );
        CHECK( game.getState() == TicTacToe::State::VictoryX );

        game.setToken( TicTacToe::Token::O, 2, 0 );
        game.setToken( TicTacToe::Token::O, 1, 1 );
        game.setToken( TicTacToe::Token::O, 0, 2);
        CHECK( game.getState() == TicTacToe::State::VictoryO );
    }
}
