#include "StrongAI/World/TicTacToe/TicTacToeHuman.hpp"

TicTacToeHuman::TicTacToeHuman( int inputSize, int outputSize, int maxInput, int maxOutput )
    : HumanAI( inputSize, outputSize, maxInput, maxOutput )
{

}

void TicTacToeHuman::visualizeInput( const std::vector< double >& input )
{
    std::cout << inputToChar( input[ 6 ] ) << "_|_" << inputToChar( input[ 7 ] ) << "_|_" << inputToChar( input[ 8 ] ) << std::endl;
    std::cout << inputToChar( input[ 3 ] ) << "_|_" << inputToChar( input[ 4 ] ) << "_|_" << inputToChar( input[ 5 ] ) << std::endl;
    std::cout << inputToChar( input[ 0 ] ) << " | " << inputToChar( input[ 1 ] ) << " | " << inputToChar( input[ 2 ] ) << std::endl;
}

std::vector< double > TicTacToeHuman::coreOutput( const std::vector< double >& input )
{
    std::cout << "TicTacToe Board:" << std::endl
        << "================" << std::endl;

    visualizeInput( input );
    std::cout << std::endl;

    std::cout << "What is your move? ( Use NumPad )" << std::endl
        << "===============================" << std::endl;

    int userInput;
    do
    {
        std::cout << "";
        std::cin >> userInput;
    }while( userInput < 1 || userInput > 9 );
    std::cout << std::endl;

    std::vector< double > output( 9, 0 );
    output.at( userInput - 1 ) = 1;
    return output;
}

char TicTacToeHuman::inputToChar( double input )
{
    if( input <= -.5f ) return 'X';
    if( input >=  .5f ) return 'O';
    else return ' ';
}
