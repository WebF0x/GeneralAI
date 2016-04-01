#include "StrongAI/World/TicTacToe/TicTacToe.hpp"

TicTacToe::Token TicTacToe::match( GeneralAI& playerX, GeneralAI& playerO )
{
    /// Precondition:
    /// Players are the kind GeneralAI( 9, 9, 1, 1 )
    if(
        playerX.INPUT_SIZE != 9 ||
        playerX.OUTPUT_SIZE != 9 ||
        playerX.INPUT_AMPLITUDE != 1 ||
        playerX.OUTPUT_AMPLITUDE != 1 ||

        playerO.INPUT_SIZE != 9 ||
        playerO.OUTPUT_SIZE != 9 ||
        playerO.INPUT_AMPLITUDE != 1 ||
        playerO.OUTPUT_AMPLITUDE != 1
      )
    {
        throw invalid_argument( std::string("Incompatible GeneralAI properties") );
    }

    /// Let AI's know this is the start of a new game
    playerX.reset();
    playerO.reset();

    /// Empty board of 9 empty squares
    std::vector< Token > board = std::vector< Token >( 9, Token::None );

    /// Pick random first player
    GeneralAI *currentPlayer = &playerX;
    GeneralAI *waitingPlayer = &playerO;

    if( GeneralAI::randomProbability() < .5f )
    {
        swap( currentPlayer, waitingPlayer );
    }

    /// Play match
    while( true )
    {
        // Create input to be sent to player
        std::vector< float > input( 9 ) ;
        for( int i = 0; i < 9; i++ )
        {
            switch( board.at( i_ ) )
            {
                case Token::None:
                    input.at( i ) = 0;
                    break;

                case Token::X:
                    input.at( i ) = 1;
                    break;

                case Token::O:
                    input.at( i ) = -1;
                    break;
            }

            if( currentPlayer == &playerO )
            {
                input.at( i ) *= -1; // That way, for every player, 1 means your token and -1 the enemy's token
            }
        }

        // Ask player for his move
        int playerMove = getPlayerMove(*currentPlayer, input );

        // Make sure playerMove is valid
        while( board[ playerMove ] != Token::None ) // Illegal move: Square not empty
        {
            currentPlayer->learn( ILLEGAL_MOVE_WORTH );

            // Learn from other player's success / failure
            auto lastLesson = currentPlayer->lastLesson();
            waitingPlayer->learn( lastLesson );

            playerMove = getPlayerMove(*currentPlayer, input );
        }

        // Player plays his move
        Token turn = ( currentPlayer == &playerX ) ? Token::X : Token::O;
        board.at( playerMove ) = turn;

        // Check endgame conditions
        if( isWinning( board, turn ) )
        {
            // Teach lessons to players
            auto winningDecision = currentPlayer->lastDecision();
            auto losingDecision = waitingPlayer->lastDecision();

            playerX.learn( winningDecision, WON_GAME_WORTH );
            playerX.learn( losingDecision, LOST_GAME_WORTH );

            playerO.learn( winningDecision, WON_GAME_WORTH );
            playerO.learn( losingDecision, LOST_GAME_WORTH );

            return turn;
        }
        else if( boardIsFull( board ) )
        {
            // Teach lessons to players
            auto decisionCurrentPlayer = currentPlayer->lastDecision();
            auto decisionWaitingPlayer = waitingPlayer->lastDecision();

            playerX.learn( decisionCurrentPlayer, TIE_GAME_WORTH );
            playerX.learn( decisionWaitingPlayer, TIE_GAME_WORTH );

            playerO.learn( decisionCurrentPlayer, TIE_GAME_WORTH );
            playerO.learn( decisionWaitingPlayer, TIE_GAME_WORTH );

            return Token::None;
        }
        else /// Game is not over: Give turn to other player
        {
            swap( currentPlayer, waitingPlayer );
        }
    }
}

/**
*   Input of the kind: [ 0, 0, 0, 1, -1, 0, -1, -1, 1 ]
*   Returns an index in range [ 0, 8 ]
**/
int TicTacToe::getPlayerMove( GeneralAI& player, const std::vector< float >& input )
{
    std::vector< float > output = player.output( input );

    // Player move is the output with the biggest value
    float playerMove = 0;
    for( unsigned int i = 0; i < output.size(); i++ )
    {
        if( output.at( i ) > output.at( playerMove ) )
        {
            playerMove = i;
        }
    }

    return playerMove;
}

bool TicTacToe::isWinning( const std::vector< Token >& board, Token turn )
{
    /// Format in a 3X3 board
    Token formattedBoard[ 3 ][ 3 ];
    for( int i = 0; i < 3; i++ )
    {
        for( int j = 0; j < 3; j++ )
        {
            formattedBoard[ i ][ j ] = board.at( i * 3 + j_ );
        }
    }

    /// Check rows
    for ( int i = 0; i < 3; i++ )
    {
        if ( ( formattedBoard[ i ][ 0 ] == turn ) && ( formattedBoard[ i ][ 1 ] == turn ) && ( formattedBoard[ i ][ 2 ] == turn ) )
            return true;
    }

    /// Check columns
    for ( int j = 0; j < 3; j++ )
    {
        if ( ( formattedBoard[ 0 ][ j ] == turn ) && ( formattedBoard[ 1 ][ j ] == turn ) && ( formattedBoard[ 2 ][ j ] == turn ) )
            return true;
    }

    /// Check diagonals
    if ( ( ( formattedBoard[ 0 ][ 0 ] == turn ) && ( formattedBoard[ 1 ][ 1 ] == turn ) && ( formattedBoard[ 2 ][ 2 ] == turn ) ) ||
        ( ( formattedBoard[ 2 ][ 0 ] == turn ) && ( formattedBoard[ 1 ][ 1 ] == turn ) && ( formattedBoard[ 0 ][ 2 ] == turn ) ) )
    {
        return true;
    }

    return false;
}

bool TicTacToe::boardIsFull( const std::vector< Token >& board )
{
    auto emptySquare = find( board.begin(), board.end(), Token::None );
    return ( emptySquare == board.end() );  // Cannot find empty square
}

