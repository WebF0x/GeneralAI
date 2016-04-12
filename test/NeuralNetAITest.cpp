#include "UnitTest++/UnitTest++.h"

#include "StrongAI/AI/NeuralNetAI/NeuralNetAI.hpp"

SUITE( NeuralNetAITest )
{
    TEST( smokeTest )
    {
        NeuralNetAI ai( 0, 0, 0, 0 );

        auto output = ai.output();
        CHECK_EQUAL( 0, output.size() );

        ai.learn( 1 );
    }

    TEST( saveAndLoad )
    {
        const std::string saveFileName = "NeuralNetAI.save";
        const int inputSize       = 1;
        const int outputSize      = 1;
        const int inputAmplitude  = 1;
        const int outputAmplitude = 1;
        const double tolerance    = 0.01;

        NeuralNetAI originalAI = NeuralNetAI( inputSize, outputSize, inputAmplitude, outputAmplitude );
        NeuralNetAI cloneAI    = NeuralNetAI( inputSize, outputSize, inputAmplitude, outputAmplitude );

        originalAI.mutate();
        cloneAI.mutate();

        GeneralAI::save< NeuralNetAI >( originalAI, saveFileName );
        GeneralAI::load< NeuralNetAI >( cloneAI,    saveFileName );

        const auto cloneOutput    = cloneAI.output();
        const auto originalOutput = originalAI.output();

        CHECK_ARRAY_CLOSE( originalOutput, cloneOutput, outputSize, tolerance );

        // Delete save file
        CHECK( !remove( saveFileName.data() ) ) ;
    }
}
