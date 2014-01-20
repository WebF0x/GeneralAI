#include "TicTacToe.h"

using namespace std;

TicTacToe::TicTacToe() : turn(X), gameOver(false)
{
    clearBoard();

    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    randomGenerator = new default_random_engine(seed);
}

TicTacToe::~TicTacToe()
{
}

void TicTacToe::match(  player1, GeneralAI* player2)
{
    clearBoard();

    ///Pick first player
    uniform_int_distribution<int> distribution(0,1);
    if(distribution(*randomGenerator) == 0)
    {
        turn = X;
    }
    else
    {
        turn = O;
    }

    vector<int> currentGameState(9);   /// Input of AI

    gameOver = false;
    while (!gameOver)
    {
        currentGameState.clear();

        for(unsigned int i=0;i<9;++i)
        {
            currentGameState.push_back(turn*board[i]);  //For the AI, the token's value doesn't matter. What matters is if it is his token or the enemy's
        }

        GeneralAI* player;
        if(turn == X)
        {
            player = player1;
        }
        else
        {
            player = player2;
        }

        //Guaranteed to be a vector of 1 element in [-4, 4]
        //Grab that element and add 4. It gives the board vector index
        int playerMove = player->output(currentGameState)[0] + 4;

        playerAction(player, playerMove);
    }
}

void TicTacToe::playerAction(player, playerMove)
{

}

void TicTacToe::clearBoard()
{
    board = vector<int>(9, EMPTY);
}

void TicTacToe::receiveMsg(Message msg)
{
    if(!gameOver)
    {
        int entree = msg.data[0];

        ///Changer le symbole de la case choisie
        board[entree-1] = turn;

        ///Vérifier victoire
        if(isWinning(turn))
        {
            msg.feedback = 1;
            gameOver = true;
        }

        ///Vérifier égalité
        else if (boardFull())
        {
            msg.feedback = 0;
            gameOver = true;
        }

        ///Changer de turn de joueur
        if (turn == X)
        {
            turn = O;
        }
        else
        {
            turn = X;
        }
    }
}

bool TicTacToe::isWinning(int turn)
{
    ///Mettre sous forme d'un board 3X3
    int jeu[3][3];
    for(int i(0); i<3; i++)
    {
        for(int j(0); j<3; j++)
        {
            jeu[i][j] = board[i*3+j];
        }
    }

    ///Vérifie horizontalement
    for (int i(0);i<3;i++)
    {
        if ((jeu[i][0]==turn)&&(jeu[i][1]==turn)&&(jeu[i][2]==turn))
            return true;
    }

    ///Vérifie verticalement
    for (int j(0);j<3;j++)
    {
        if ((jeu[0][j]==turn)&&(jeu[1][j]==turn)&&(jeu[2][j]==turn))
            return true;
    }

    ///Check diagonal
    if (((jeu[0][0]==turn)&&(jeu[1][1]==turn)&&(jeu[2][2]==turn)) || ((jeu[2][0]==turn)&&(jeu[1][1]==turn)&&(jeu[0][2]==turn)))
    {
        return true;
    }

    return false;
}

bool TicTacToe::boardFull()
{
    bool isFull = true;
    for(int i(0); i<9; i++)
    {
        if (board[i] == EMPTY)
            isFull = false;
    }
    return isFull;
}

