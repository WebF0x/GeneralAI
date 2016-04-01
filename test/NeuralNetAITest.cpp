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
}
