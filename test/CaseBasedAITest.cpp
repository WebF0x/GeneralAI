#include "UnitTest++/UnitTest++.h"

#include "StrongAI/AI/CaseBasedAI/CaseBasedAI.hpp"

SUITE( CaseBasedAITest )
{

    TEST( smokeTest )
    {
        CaseBasedAI ai( 0, 0, 0, 0 );

        auto output = ai.output();
        CHECK_EQUAL( 0, output.size() );

        ai.learn( 1 );
    }

    TEST( seeksGoodOutcome )
    {
        CaseBasedAI ai( 1, 1, 1, 2 );

        const std::vector< float > input( { 0 } );
        const std::vector< float > outputToLearn( { 2 } );

        ai.learn( input, outputToLearn, 1 );
        auto actualOutput = ai.output( input );
        CHECK( 2 == actualOutput.at( 0 ) );
    }

    TEST( avoidsBadOutcome )
    {
        CaseBasedAI ai( 1, 1, 1, 2 );

        const std::vector< float > input( { 0 } );
        const std::vector< float > outputToLearn( { 2 } );

        ai.learn( input, outputToLearn, -1 );
        auto actualOutput = ai.output( input );
        CHECK( 2 != actualOutput.at( 0 ) );
    }
}
