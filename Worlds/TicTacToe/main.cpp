#include "TicTacToe.h"

using namespace std;

int main()
{
    TicTacToe* game   = new TicTacToe();

    GeneralAI* player = new CaseBasedAI(9, 1, 1, 9);
    const unsigned int nbGames = 1;

    for(unsigned int i=0; i<nbGames; ++i)
    {
        game->match(player, player);
    }
    delete player;



    delete game;
    return 0;
}
