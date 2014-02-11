#include "TicTacToe.h"
#include "../../AIs/CaseBasedAI/CaseBasedAI.h"
#include "../../AIs/HumanAI/HumanAI.h"
#include "../../AIs/RandomAI/RandomAI.h"

using namespace std;

int main()
{
    /// Initialization
    //const int NUMBER_OF_GAMES = 1000;
    const string SAVE_FILE_X = "TicTacToeX.save";
    const string SAVE_FILE_O = "TicTacToeO.save";

    TicTacToe game;
    GeneralAI* playerX = new CaseBasedAI(9, 1, 1, 4);
    GeneralAI* playerO = new RandomAI(9, 1, 1, 4);

    ///Stats
    vector<bool> recentGamesResults(100);

    ///Load AI save files if they exist
    try
    {
        playerX->load(SAVE_FILE_X);
    }
    catch(fstream::failure e)
    {
        //Do nothing
    }

    try
    {
        playerO->load(SAVE_FILE_O);
    }
    catch(fstream::failure e)
    {
        //Do nothing
    }

    /// Play games
    for(unsigned int i=0; ; ++i)
    {
        TicTacToe::Token winner;
        winner = game.match(*playerX, *playerO);

        switch(winner)
        {
            case TicTacToe::Token::None:
                recentGamesResults[i%100] = false;
                break;

            case TicTacToe::Token::X:
                recentGamesResults[i%100] = true;
                break;

            case TicTacToe::Token::O:
                recentGamesResults[i%100] = false;
                break;
        }

        if(i>=100)  //Start checking stats
        {
            int totalWins=0;
            for(unsigned int i=0; i<recentGamesResults.size(); ++i)
            {
                if(recentGamesResults[i])
                {
                    ++totalWins;
                }
            }

            float winRatio = float(totalWins)/100.f;
            //cout<<"Game #"<<i<<" ratio: "<<winRatio<<endl;

            if(winRatio >= .9f)
            {
                cout<<"It took "<<i<<" games to be so awesome!"<<endl;
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
