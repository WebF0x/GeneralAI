#include <iostream>
#include "StrongAI/AI/ExampleAI/ExampleAI.hpp"

int main()
{
    const int INPUT_SIZE( 2 ), OUTPUT_SIZE( 2 );
    const int INPUT_AMPLITUDE( 2 ), OUTPUT_AMPLITUDE( 2 );
    const std::string FILE_NAME = "example.save";

    ExampleAI ai = ExampleAI( INPUT_SIZE, OUTPUT_SIZE, INPUT_AMPLITUDE, OUTPUT_AMPLITUDE );

    std::vector< double > input( INPUT_SIZE );

    std::cout << "Input:" << std::endl;
    for( auto val : input )
    {
        std::cout << '\t' << val << std::endl;
    }

    /// Test output
    std::vector< double > output = ai.output( input );

    std::cout << "Output:" << std::endl;
    for( auto value : output )
    {
        std::cout << '\t' << value << std::endl;
    }

    /// Test learn
    double outcome = -1;
    ai.learn( input, output, outcome );

    /// Test save / load
    GeneralAI::save< ExampleAI >( ai, FILE_NAME );

    ExampleAI clone( 0, 0, 0, 0 );
    GeneralAI::load< ExampleAI >( clone, FILE_NAME );

    if( clone.INPUT_SIZE        == INPUT_SIZE       &&
        clone.OUTPUT_SIZE       == OUTPUT_SIZE      &&
        clone.INPUT_AMPLITUDE   == INPUT_AMPLITUDE  &&
        clone.OUTPUT_AMPLITUDE  == OUTPUT_AMPLITUDE )
    {
        std::cout << "Save and load successful!" << std::endl;
    }

    /// Test JSON save format
    const std::string JSON_FILE_NAME = "example.JSON";
    GeneralAI::save< ExampleAI, cereal::JSONOutputArchive >( clone, JSON_FILE_NAME );
    std::cout    << std::endl
            << "Open the file " << JSON_FILE_NAME << "!" << std::endl
            << "JSON is a human readable format really useful for debugging!" << std::endl
            << "You can also use XML" << std::endl
            << "You can also use the default format ( binary ) when you are done debugging, it is way more efficient" << std::endl;

    return 0;
}
