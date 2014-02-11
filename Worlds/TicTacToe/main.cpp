#include "TicTacToe.h"
#include "TicTacToeHuman.h"
#include "../../AIs/CaseBasedAI/CaseBasedAI.h"
#include "../../AIs/HumanAI/HumanAI.h"
#include "../../AIs/RandomAI/RandomAI.h"

using namespace std;

bool verboseEndGame(TicTacToe::Token, int);

int main()
{
    /// Initialization
    const unsigned int NUMBER_OF_GAMES = 1000; //-1 to play an infinite number of games
    const string SAVE_FILE_X = "TicTacToeX.save";
    const string SAVE_FILE_O = "TicTacToeO.save";
    const bool VERBOSE_ENABLED = false;

    TicTacToe game;
    GeneralAI* playerX = new RandomAI(9, 1, 1, 4);
    GeneralAI* playerO = new CaseBasedAI(9, 1, 1, 4);       //if(VERBOSE_ENABLED): the stats are calculated for playerO

    ///Load AI save files if they exist
    try {playerX->load(SAVE_FILE_X); }
        catch(fstream::failure e) { /*Do nothing*/ }
    try {playerO->load(SAVE_FILE_O); }
        catch(fstream::failure e) { /*Do nothing*/ }

    /// Play games
    for(unsigned int i=0; i != NUMBER_OF_GAMES; ++i)
    {
        TicTacToe::Token winner;
        winner = game.match(*playerX, *playerO);

        if(VERBOSE_ENABLED)
        {
            if (!verboseEndGame(winner, i))  //false if must stop for some reason
            {
                break;
            }
        }
    }

    playerX->save(SAVE_FILE_X);
    playerO->save(SAVE_FILE_O);

    delete playerX;
    delete playerO;

    return 0;
}

bool verboseEndGame(TicTacToe::Token winner, int gameNumber)
{
    ///Stats
    static vector<bool> recentGamesResults(100);

    ///Evaluation
    switch(winner)
    {
        case TicTacToe::Token::None:
            cout<<"Tie game!"<<endl<<endl;
            recentGamesResults[gameNumber%100] = false;
            break;

        case TicTacToe::Token::X:
            cout<<"Player X wins!"<<endl<<endl;
            recentGamesResults[gameNumber%100] = true;
            break;

        case TicTacToe::Token::O:
            cout<<"Player O wins!"<<endl<<endl;
            recentGamesResults[gameNumber%100] = false;
            break;
    }

    ///More stats stuff
    if(gameNumber>=100)  //Start checking stats
    {
        int totalWins=0;
        for(unsigned int i=0; i<recentGamesResults.size(); ++i)
        {
            if(recentGamesResults[i])
            {
                ++totalWins;
            }
        }

        float winPercentage = float(totalWins)/100.f;
        cout<<"Game #"<<gameNumber<<" winPercentage: "<<winPercentage<<endl;

        if(winPercentage >= .9f)
        {
            cout<<"It took "<<gameNumber<<" games to be so awesome!"<<endl;
            return false;
        }
    }

    return true;
}
