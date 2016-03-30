#include <iostream>
#include "StrongAI/AI/HumanAI/HumanAI.hpp"

using namespace std;

int main()
{
    const unsigned int inputSize( 3 ), outputSize( 1 );
    const int maxInput( 3 ), maxOutput( 100 );
    const string fileName = "memory.txt";

    HumanAI ai( inputSize, outputSize, maxInput, maxOutput );

    GeneralAI::load< HumanAI, cereal::JSONInputArchive >( ai, fileName );

    vector< float > input  = { 1, 2, 3 };
    vector< float > output = ai.output( input );

    cout << "Your output is: " << output.at( 0 ) << endl;

    GeneralAI::save< HumanAI, cereal::JSONOutputArchive >( ai, fileName );

    return 0;
}
