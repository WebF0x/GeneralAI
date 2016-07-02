#include <iostream>
#include "AI/HumanAI/HumanAI.hpp"

int main()
{
    const unsigned int inputSize( 3 ), outputSize( 1 );
    const int maxInput( 3 ), maxOutput( 100 );
    const std::string fileName = "memory.txt";

    HumanAI ai( inputSize, outputSize, maxInput, maxOutput );

    GeneralAI::load< HumanAI, cereal::JSONInputArchive >( ai, fileName );

    std::vector< double > input  = { 1, 2, 3 };
    std::vector< double > output = ai.output( input );

    std::cout << "Your output is: " << output.at( 0 ) << std::endl;

    GeneralAI::save< HumanAI, cereal::JSONOutputArchive >( ai, fileName );

    return 0;
}
