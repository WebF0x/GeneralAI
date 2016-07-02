#include <iostream>
#include "AI/RandomAI/RandomAI.hpp"

int main()
{
    const unsigned int inputSize( 10 ), outputSize( 10 );
    const int maxInput( 3 ), maxOutput( 100 );
    const std::string fileName = "myDummySave.txt";

    RandomAI *ai = new RandomAI( inputSize, outputSize, maxInput, maxOutput );

    // output
    try
    {
        std::vector< double > v( inputSize );
        std::vector< double > v2 = ai->output( v );

        for( unsigned int i = 0; i < outputSize; i++ )
        {
            std::cout << v2[ i ] << std::endl;
        }
    }
    catch( exception& e_ )
    {
        std::cout << e.what() << std::endl;
    }

    // learn
    try
    {
        std::vector< double > input( inputSize ), output( outputSize );
        double outcome = -1;
        ai->learn( input, output, outcome );
    }
    catch( exception& e_ )
    {
        std::cout << e.what() << std::endl;
    }

    // Delete GeneralAI
    delete ai;

    return 0;
}
