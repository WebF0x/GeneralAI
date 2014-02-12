#include "TicTacToe.h"

using namespace std;

TicTacToe::TicTacToe()
{
    /// Random
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    randomGenerator = default_random_engine(seed);
}

TicTacToe::~TicTacToe()
{
}

TicTacToe::Token TicTacToe::match(GeneralAI& playerX, GeneralAI& playerO)
{
    ///Precondition:
    ///-Players are the kind GeneralAI(9,1,1,4)
    if(
        playerX.INPUT_SIZE != 9 ||
        playerX.INPUT_AMPLITUDE != 1 ||
        playerX.OUTPUT_SIZE != 1 ||
        playerX.OUTPUT_AMPLITUDE != 4 ||

        playerO.INPUT_SIZE != 9 ||
        playerO.INPUT_AMPLITUDE != 1 ||
        playerO.OUTPUT_SIZE != 1 ||
        playerO.OUTPUT_AMPLITUDE != 4
      )
    {
        throw invalid_argument(string("Invalid GeneralAI properties"));
    }

    ///Let AI's know this is the start of a new game
    playerX.reset();
    playerO.reset();

    /// Empty board of 9 empty squares
    vector<Token> board = vector<Token>(9, Token::None);

    ///Pick random first player
    GeneralAI *currentPlayer = &playerX;
    GeneralAI *waitingPlayer = &playerO;
    uniform_int_distribution<int> distribution(0,1);
    if(distribution(randomGenerator) == 0)
    {
        swap(currentPlayer,waitingPlayer);
    }


    ///Play match
    while(true)
    {
        //Create data to be sent to player
        vector<int> input(9);
        for(int i=0; i<9; ++i)
        {
            switch(board[i])
            {
                case Token::None:
                    input[i] = 0;
                    break;

                case Token::X:
                    input[i] = 1;
                    break;

                case Token::O:
                    input[i] = -1;
                    break;
            }

            if(currentPlayer == &playerO)
            {
                input[i] *= -1; //That way, for every player, 1 means your token and -1 the enemy's token
            }
        }

        //Ask player for his move
        int playerMove = getPlayerMove(*currentPlayer, input);

        //Make sure playerMove is valid
        while(board[playerMove] != Token::None) //Illegal move: Square not empty
        {
            currentPlayer->learn(ILLEGAL_MOVE_WORTH);

            //Learn from other player's success/failure
            auto lastLesson = currentPlayer->lastLessonLearned();
            waitingPlayer->learn(lastLesson);

            playerMove = getPlayerMove(*currentPlayer, input);
        }

        //Player plays his move
        Token turn;

        if(currentPlayer == &playerX)
        {
            turn = Token::X;
        }
        else
        {
            turn = Token::O;
        }

        board[playerMove] = turn;


        /// Check endgame conditions
        if(isWinning(board, turn))
        {
            //Reward and Punish appropriate player
            if(currentPlayer == &playerX)
            {
                playerX.learn(WON_GAME_WORTH);
                playerO.learn(LOST_GAME_WORTH);

                return Token::X;
            }
            else
            {
                playerX.learn(LOST_GAME_WORTH);
                playerO.learn(WON_GAME_WORTH);

                return Token::O;
            }

            //Learn from other player's success/failure
            auto lastLessonX = playerX.lastLessonLearned();
            auto lastLessonO = playerO.lastLessonLearned();

            playerX.learn(lastLessonO);
            playerO.learn(lastLessonX);
        }
        else if(boardIsFull(board))
        {
            playerX.learn(TIE_GAME_WORTH);
            playerO.learn(TIE_GAME_WORTH);

            //Learn from other player's success/failure
            auto lastLessonX = playerX.lastLessonLearned();
            auto lastLessonO = playerO.lastLessonLearned();

            playerX.learn(lastLessonO);
            playerO.learn(lastLessonX);

            return Token::None;
        }
        else ///Game is not over: Give turn to other player
        {
            swap(currentPlayer,waitingPlayer);
        }
    }
}

int TicTacToe::getPlayerMove(GeneralAI& player, const vector<int>& input)
{
    return player.output(input)[0] + 4; //We want the value to be in range [0,8]
}

bool TicTacToe::isWinning(const vector<Token>& board, Token turn)
{
    ///Format in a 3X3 board
    Token formattedBoard[3][3];
    for(int i=0; i<3; ++i)
    {
        for(int j=0; j<3; ++j)
        {
            formattedBoard[i][j] = board[i*3+j];
        }
    }

    ///Check rows
    for (int i=0;i<3;++i)
    {
        if ((formattedBoard[i][0]==turn)&&(formattedBoard[i][1]==turn)&&(formattedBoard[i][2]==turn))
            return true;
    }

    ///Check columns
    for (int j=0;j<3;++j)
    {
        if ((formattedBoard[0][j]==turn)&&(formattedBoard[1][j]==turn)&&(formattedBoard[2][j]==turn))
            return true;
    }

    ///Check diagonals
    if (((formattedBoard[0][0]==turn)&&(formattedBoard[1][1]==turn)&&(formattedBoard[2][2]==turn)) || ((formattedBoard[2][0]==turn)&&(formattedBoard[1][1]==turn)&&(formattedBoard[0][2]==turn)))
    {
        return true;
    }

    return false;
}

bool TicTacToe::boardIsFull(const vector<Token>& board)
{
    for(int i=0; i<9; ++i)
    {
        if (board[i] == Token::None)
            return false;
    }

    return true;
}

