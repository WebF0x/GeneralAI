#include <iostream>
#include "StrongAI/AI/RandomAI/RandomAI.hpp"

int main()
{
    const unsigned int inputSize( 10 ), outputSize( 10 );
    const int maxInput( 3 ), maxOutput( 100 );
    const std::string fileName = "myDummySave.txt";

    RandomAI *ai = new RandomAI( inputSize, outputSize, maxInput, maxOutput );

    // output
    try
    {
        std::vector< float > v( inputSize );
        std::vector< float > v2 = ai->output( v );

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
        std::vector< float > input( inputSize ), output( outputSize );
        float outcome = -1;
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
