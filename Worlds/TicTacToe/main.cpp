#include "TicTacToe.h"
#include "TicTacToeHuman.h"
#include "../../AIs/CaseBasedAI/CaseBasedAI.h"
#include "../../AIs/RandomAI/RandomAI.h"

using namespace std;

bool verboseEndGame(TicTacToe::Token);

int main()
{
    /// Initialization
    const unsigned int NUMBER_OF_GAMES = 100000; //-1 to play an infinite number of games
    const string SAVE_FILE_X = "TicTacToeX.save";
    const string SAVE_FILE_O = "TicTacToeO.save";
    const bool VERBOSE_ENABLED = false;          //if(VERBOSE_ENABLED): the stats are calculated for playerO. Use with small NUMBER_OF_GAMES or with a human player


    TicTacToe game;
    //GeneralAI* playerX = new TicTacToeHuman(9, 1, 1, 4);
    //GeneralAI* playerX = new RandomAI(9, 1, 1, 4);
    GeneralAI* playerX = new CaseBasedAI(9, 1, 1, 4);
    GeneralAI* playerO = new CaseBasedAI(9, 1, 1, 4);

    ///Load AI save files if they exist
    playerX->load(SAVE_FILE_X);
    playerO->load(SAVE_FILE_O);

    /// Play games
    for(unsigned int i=0; i != NUMBER_OF_GAMES; ++i)
    {
        TicTacToe::Token winner;
        winner = game.match(*playerX, *playerO);

        if(VERBOSE_ENABLED)
        {
            if (!verboseEndGame(winner))  //false if must stop for some reason
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

bool verboseEndGame(TicTacToe::Token winner)
{
    ///Stats
    static vector<bool> recentGamesResults(100);
    static int gameNumber = 0;

    ///Evaluation
    switch(winner)
    {
        case TicTacToe::Token::None:
            cout<<"Tie game!"<<endl<<endl;
            break;

        case TicTacToe::Token::X:
            cout<<"Player X wins!"<<endl<<endl;
            recentGamesResults[gameNumber%100] = false;
            ++gameNumber;
            break;

        case TicTacToe::Token::O:
            cout<<"Player O wins!"<<endl<<endl;
            recentGamesResults[gameNumber%100] = true;
            ++gameNumber;
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
