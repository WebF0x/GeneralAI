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

using namespace std;

bool verboseEndGame( TicTacToe::Token winner );

void manualTesting( unique_ptr< NeuralNetAI >& ai )
{
    TicTacToeHuman human( 9, 9, 1, 1 );
    TicTacToe game;
    const int NUM_OF_GAMES = 10;

    for( int i = 0; i < NUM_OF_GAMES; i++ )
    {
        TicTacToe::Token winner = game.match(*ai, human );
        verboseEndGame( winner );
    }
}

class AdderDarwinAI : public DarwinAI
{
    public:
    AdderDarwinAI() : DarwinAI( 9, 9, 1, 1 )
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

            uniform_int_distribution< int > distribution( 0, m_population.size() );
            randomIndex = distribution( GeneralAI::m_randomNumberGenerator );

            TicTacToe::Token winner = game.match( ai, *m_population.at( randomIndex ) );

            if( winner == TicTacToe::Token::X_ )
            {
                score += 1;
            }
            else if( winner == TicTacToe::Token::O_ )
            {
                score -= 1;
            }
        }

        return score;
    }
};

int main()
{
    cout << "Generating initial population" << endl;
    AdderDarwinAI population;

    cout << "Population is evolving" << endl;
    for( int i = 0; i < 100; i++)
    {
        cout << "\t" << i << " %" << endl;
        population.evolve( 100 );
    }

    cout << "Saving population" << endl;
    // GeneralAI::save< AdderDarwinAI >, cereal::JSONOutputArchive >( AdderDarwinAI, "save.txt" );

    cout << "Selecting best individual" << endl;
    unique_ptr< NeuralNetAI >& champion = population.bestIndividual();

    cout << "Manual Testing" << endl;
    manualTesting( champion );

    return 0;
}

bool verboseEndGame( TicTacToe::Token winner )
{
    /// Stats
    static vector< bool > recentGamesResults( 100 );
    static int gameNumber = 0;

    /// Evaluation
    switch( winner )
    {
        case TicTacToe::Token::None:
            cout << "Tie game!" << endl << endl;
            break;

        case TicTacToe::Token::X:
            cout << "Player X wins!" << endl << endl;
            recentGamesResults[ gameNumber % 100 ] = false;
            gameNumber++;
            break;

        case TicTacToe::Token::O:
            cout << "Player O wins!" << endl << endl;
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
        cout << "Game #" << gameNumber << " winPercentage: " << winPercentage << endl;

        if( winPercentage >= .9f )
        {
            cout << "It took " << gameNumber << " games to be so awesome!" << endl;
            return false;
        }
    }

    return true;
}
