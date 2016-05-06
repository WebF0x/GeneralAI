#include <iostream>
#include <fstream>
#include "StrongAI/AI/NeuralNetAI/NeuralNetAI.hpp"
#include "StrongAI/AI/DarwinAI/DarwinAI.hpp"
#include <map>
#include <ctime>
#include "StrongAI/World/DarwinTicTacToe/TicTacToe.hpp"
#include "StrongAI/World/DarwinTicTacToe/TicTacToeHuman.hpp"
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>

bool verboseEndGame( TicTacToe::Token winner );

void manualTesting( NeuralNetAI& ai )
{
    TicTacToeHuman human( 9, 9, 1, 1 );
    TicTacToe game;
    const int NUM_OF_GAMES = 10;

    for( int i = 0; i < NUM_OF_GAMES; i++ )
    {
        TicTacToe::Token winner = game.match(ai, human );
        verboseEndGame( winner );
    }
}

class AdderDarwinAI : public DarwinAI
{
    public:
    AdderDarwinAI() : DarwinAI( 9, 9, 1, 1, 10 )
    {

    }

    private:

    // Task: Play TicTacToe
    virtual float fitnessEval( NeuralNetAI& ai )
    {
        TicTacToe game;
        float score = 0;
        const int NUM_OF_GAMES = 1;

        for( int i = 0; i < NUM_OF_GAMES; i++ )
        {
            int randomIndex;
            std::uniform_int_distribution< int > distribution( 0, m_population.size() );
            randomIndex = distribution( GeneralAI::m_randomNumberGenerator );

            TicTacToe::Token winner = game.match( ai, m_population.at( randomIndex ) );

            if( winner == TicTacToe::Token::X )
            {
                score += 1;
            }
            else if( winner == TicTacToe::Token::O )
            {
                score -= 1;
            }
        }

        return score;
    }
};

int main()
{
    std::cout << "Generating initial population" << std::endl;
    AdderDarwinAI population;

    std::cout << "Population is evolving" << std::endl;
    for( int i = 0; i < 100; i++)
    {
        std::cout << "\t" << i << " %" << std::endl;
        population.evolve( 2 );
    }

    std::cout << "Saving population" << std::endl;
    GeneralAI::save< AdderDarwinAI, cereal::JSONOutputArchive >( population, "save.txt" );

    std::cout << "Selecting best individual" << std::endl;
    NeuralNetAI& champion = population.bestIndividual();

    std::cout << "Manual Testing" << std::endl;
    manualTesting( champion );

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
