#include "StrongAI/World/TicTacToe/TicTacToe.hpp"
#include "StrongAI/World/TicTacToe/TicTacToeHuman.hpp"
#include "StrongAI/AI/CaseBasedAI/CaseBasedAI.hpp"
#include "StrongAI/AI/NeuralNetAI/NeuralNetAI.hpp"
#include "StrongAI/AI/RandomAI/RandomAI.hpp"

bool verboseEndGame( TicTacToe::Token );

int main()
{
    /// Initialization
    const unsigned int NUMBER_OF_GAMES = 1000; //-1 to play an infinite number of games
    const std::string SAVE_FILE_X = "TicTacToeX.save";
    const std::string SAVE_FILE_O = "TicTacToeO.save";
    const bool VERBOSE_ENABLED = false;          // if( VERBOSE_ENABLED ): the stats are calculated for playerO. Use with small NUMBER_OF_GAMES or with a human player

    TicTacToe game;

    CaseBasedAI playerX( 9, 9, 1, 1 );
    TicTacToeHuman playerO( 9, 9, 1, 1 );
    // CaseBasedAI playerO( 9, 9, 1, 1 );

    std::cout << "start load" << std::endl;

    GeneralAI::load< CaseBasedAI >( playerX, SAVE_FILE_X );
    // GeneralAI::load< NeuralNetAI >( playerO, SAVE_FILE_O );
    // GeneralAI::load< CaseBasedAI >( playerO, SAVE_FILE_O );

    std::cout << "load completed" << std::endl;
    std::cout << "start games" << std::endl;

    /// Play games
    for( unsigned int i = 0; i != NUMBER_OF_GAMES; i++ )
    {
        TicTacToe::Token winner;
        winner = game.match( playerX, playerO );

        if( VERBOSE_ENABLED )
        {
            if (!verboseEndGame( winner ) )  // false if must stop for some reason
            {
                break;
            }
        }
    }

    std::cout << "games completed" << std::endl;
    std::cout << "start save" << std::endl;

    GeneralAI::save< CaseBasedAI >( playerX, SAVE_FILE_X );
    // GeneralAI::save< NeuralNetAI >( playerO, SAVE_FILE_O );
    // GeneralAI::save< CaseBasedAI >( playerO, SAVE_FILE_O );

    std::cout << "save completed" << std::endl;

    return 0;
}

bool verboseEndGame( TicTacToe::Token winner )
{
    /// Stats
    static std::vector< bool > recentGamesResults( 100 );
    static int gameNumber = 0;

    /// Evaluation
    switch( winner )
    {
        case TicTacToe::Token::None:
            std::cout << "Tie game!" << std::endl << std::endl;
            break;

        case TicTacToe::Token::X:
            std::cout << "Player X wins!" << std::endl << std::endl;
            recentGamesResults[ gameNumber % 100 ] = false;
            gameNumber++;
            break;

        case TicTacToe::Token::O:
            std::cout << "Player O wins!" << std::endl << std::endl;
            recentGamesResults[ gameNumber % 100 ] = true;
            gameNumber++;
            break;
    }

    /// More stats stuff
    if( gameNumber >= 100 )  // Start checking stats
    {
        int totalWins = 0;
        for( unsigned int i = 0; i < recentGamesResults.size(); i++ )
        {
            if( recentGamesResults[ i ] )
            {
                totalWins++;
            }
        }

        float winPercentage = float( totalWins ) / 100.f;
        std::cout << "Game #" << gameNumber << " winPercentage: " << winPercentage << std::endl;

        if( winPercentage >= .9f )
        {
            std::cout << "It took " << gameNumber << " games to be so awesome!" << std::endl;
            return false;
        }
    }

    return true;
}
