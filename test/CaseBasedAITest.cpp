#include "UnitTest++/UnitTest++.h"

#include "StrongAI/AI/CaseBasedAI/CaseBasedAI.hpp"

#include <string>
#include <vector>

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

    TEST( saveAndLoad )
    {
        const std::string saveFileName = "caseBasedAI.save";
        const std::vector< float > input( { 0 } );
        const std::vector< float > outputToLearn( { 2 } );

        CaseBasedAI teacherAI ( 1, 1, 2, 2 );
        teacherAI.learn( input, outputToLearn, 1 );
        GeneralAI::save< CaseBasedAI >( teacherAI, saveFileName );

        CaseBasedAI studentAI ( 1, 1, 2, 2 );
        GeneralAI::load< CaseBasedAI >( studentAI, saveFileName );
        auto studentOutput = studentAI.output( input );

        CHECK_EQUAL( outputToLearn.at( 0 ), studentOutput.at( 0 ) );

        // Delete save file
        CHECK( !remove( saveFileName.data() ) ) ;
    }
}
