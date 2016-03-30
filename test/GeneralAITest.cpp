#include "UnitTest++/UnitTest++.h"

#include "StrongAI/AI/GeneralAI/GeneralAI.hpp"
#include <cstdio>

class MockAI : public GeneralAI
{
    public:
        MockAI( int inputSize, int outputSize, int inputAmplitude, int outputAmplitude ) :
            GeneralAI( inputSize, outputSize, inputAmplitude, outputAmplitude )
        {

        }

    private:
        virtual void coreLearn( const std::vector< float >& input, const std::vector< float >& output, float outcome )
        {

        }

        virtual std::vector< float > coreOutput( const std::vector< float >& input )
        {
            const std::vector< float > output( OUTPUT_SIZE, 0 );
            return output;
        }

        friend cereal::access;
        template < class Archive >
        void serialize( Archive& ar )
        {
            ar( cereal::virtual_base_class< GeneralAI >( this ) );

            /**
                You can serialize any variables that you want like this:
                    ar( cereal::virtual_base_class< GeneralAI >( this ), var1, var2, ..., varN );
            **/
        }
};

SUITE( GeneralAITest )
{

    TEST( constructor )
    {
        MockAI mockAI = MockAI( 1, 2, 3, 4 );

        CHECK_EQUAL( 1, mockAI.INPUT_SIZE );
        CHECK_EQUAL( 2, mockAI.OUTPUT_SIZE );
        CHECK_EQUAL( 3, mockAI.INPUT_AMPLITUDE );
        CHECK_EQUAL( 4, mockAI.OUTPUT_AMPLITUDE );
    }

    TEST( output )
    {
        MockAI mockAI = MockAI( 1, 1, 1, 1 );
        const std::vector< float > dummyInput( 1, 0 );
        auto output = mockAI.output( dummyInput );
        CHECK_EQUAL( 1, output.size() );
    }

    TEST( outputNoParam )
    {
        std::vector< MockAI > mockAIs;
        mockAIs.push_back( MockAI( 0, 0, 0, 0 ) );
        mockAIs.push_back( MockAI( 0, 0, 0, 1 ) );
        mockAIs.push_back( MockAI( 0, 0, 1, 0 ) );
        mockAIs.push_back( MockAI( 0, 0, 1, 1 ) );

        mockAIs.push_back( MockAI( 0, 1, 0, 0 ) );
        mockAIs.push_back( MockAI( 0, 1, 0, 1 ) );
        mockAIs.push_back( MockAI( 0, 1, 1, 0 ) );
        mockAIs.push_back( MockAI( 0, 1, 1, 1 ) );

        mockAIs.push_back( MockAI( 1, 0, 0, 0 ) );
        mockAIs.push_back( MockAI( 1, 0, 0, 1 ) );
        mockAIs.push_back( MockAI( 1, 0, 1, 0 ) );
        mockAIs.push_back( MockAI( 1, 0, 1, 1 ) );

        mockAIs.push_back( MockAI( 1, 1, 0, 0 ) );
        mockAIs.push_back( MockAI( 1, 1, 0, 1 ) );
        mockAIs.push_back( MockAI( 1, 1, 1, 0 ) );
        mockAIs.push_back( MockAI( 1, 1, 1, 1 ) );

        for( auto& mockAI : mockAIs )
        {
            auto output = mockAI.output();
        }
    }

    TEST( outputNoParamZeroAmplitude )
    {
        MockAI mockAI = MockAI( 0, 0, 0, 0 );
        auto output = mockAI.output();
        CHECK_EQUAL( 0, output.size() );
    }

    TEST( outputNoParamZeroAmplitudeOutput )
    {
        MockAI mockAI = MockAI( 0, 1, 0, 0 );
        auto output = mockAI.output();
        CHECK_EQUAL( 1, output.size() );
    }

    TEST( outputNoParamZeroAmplitudeInput )
    {
        MockAI mockAI = MockAI( 0, 0, 0, 1 );
        auto output = mockAI.output();
        CHECK_EQUAL( 0, output.size() );
    }

    TEST( outputWithInvalidInputSize )
    {
        MockAI mockAI = MockAI( 0, 0, 0, 0 );
        CHECK_THROW( mockAI.output( std::vector< float >( 1, 0 ) ), std::length_error );
    }

    TEST( outputWithInvalidInputAmplitude )
    {
        MockAI mockAI = MockAI( 1, 0, 0, 0 );
        CHECK_THROW( mockAI.output( std::vector< float >( 1, 1 ) ), std::length_error );
    }

    TEST( learn )
    {
        MockAI mockAI = MockAI( 0, 0, 0, 0 );
        const std::vector< float > input( 0, 0 );
        const std::vector< float > output( 0, 0 );
        const float outcome( 0 );

        mockAI.learn( input, output, outcome );
    }

    TEST( learnWithInvalidInputSize )
    {
        MockAI mockAI = MockAI( 0, 0, 0, 0 );
        const std::vector< float > input( 1, 0 );
        const std::vector< float > output( 0, 0 );
        const float outcome( 0 );

        CHECK_THROW( mockAI.learn( input, output, outcome ), std::length_error );
    }

    TEST( learnWithInvalidOutputSize )
    {
        MockAI mockAI = MockAI( 0, 0, 0, 0 );
        const std::vector< float > input( 0, 0 );
        const std::vector< float > output( 1, 0 );
        const float outcome( 0 );

        CHECK_THROW( mockAI.learn( input, output, outcome ), std::length_error );
    }

    TEST( learnWithInvalidInputAmplitude )
    {
        MockAI mockAI = MockAI( 1, 0, 0, 0 );
        const std::vector< float > input( 1, 1 );
        const std::vector< float > output( 0, 0 );
        const float outcome( 0 );

        CHECK_THROW( mockAI.learn( input, output, outcome ), std::length_error );
    }

    TEST( learnWithInvalidOutputAmplitude )
    {
        MockAI mockAI = MockAI( 0, 1, 0, 0 );
        const std::vector< float > input( 0, 0 );
        const std::vector< float > output( 1, 1 );
        const float outcome( 0 );

        CHECK_THROW( mockAI.learn( input, output, outcome ), std::length_error );
    }

    TEST( saveAndLoad )
    {
        const std::string saveFileName = "example.save";

        MockAI mockAI = MockAI( 1, 2, 3, 4 );

        GeneralAI::save< MockAI >( mockAI, saveFileName );

        MockAI cloneAI( 0, 0, 0, 0 );
        GeneralAI::load< MockAI >( cloneAI, saveFileName );

        CHECK_EQUAL( 1, cloneAI.INPUT_SIZE );
        CHECK_EQUAL( 2, cloneAI.OUTPUT_SIZE );
        CHECK_EQUAL( 3, cloneAI.INPUT_AMPLITUDE );
        CHECK_EQUAL( 4, cloneAI.OUTPUT_AMPLITUDE );

        // Delete save file
        CHECK( !remove( saveFileName.data() ) ) ;
    }

    TEST( validInput )
    {
        MockAI mockAI = MockAI( 2, 2, 3, 3 );
        CHECK(  mockAI.validInput( std::vector< float >( 2,  3 ) ) );
        CHECK(  mockAI.validInput( std::vector< float >( 2, -3 ) ) );
        CHECK( !mockAI.validInput( std::vector< float >( 2,  3.001 ) ) );
        CHECK( !mockAI.validInput( std::vector< float >( 2, -3.001 ) ) );
    }

    TEST( validOutput )
    {
        MockAI mockAI = MockAI( 2, 2, 3, 3 );
        CHECK(  mockAI.validOutput( std::vector< float >( 2,  3 ) ) );
        CHECK(  mockAI.validOutput( std::vector< float >( 2, -3 ) ) );
        CHECK( !mockAI.validOutput( std::vector< float >( 2,  3.001 ) ) );
        CHECK( !mockAI.validOutput( std::vector< float >( 2, -3.001 ) ) );
    }

    TEST( validOutcome )
    {
        CHECK(  GeneralAI::validOutcome(  1.f ) );
        CHECK(  GeneralAI::validOutcome( -1.f ) );
        CHECK( !GeneralAI::validOutcome(  1.01f ) );
        CHECK( !GeneralAI::validOutcome( -1.01f ) );
    }

    TEST( validVectorEmpty )
    {
        CHECK( GeneralAI::validVector(  std::vector< float >( {   } ), 0, 0 ) );
        CHECK( GeneralAI::validVector(  std::vector< float >( {   } ), 0, 1 ) );

        CHECK( GeneralAI::validVector(  std::vector< float >( 0, 0 ) , 0, 0 ) );
        CHECK( GeneralAI::validVector(  std::vector< float >( 0, 1 ) , 0, 0 ) );

        CHECK( !GeneralAI::validVector(  std::vector< float >( {   } ), 1, 0 ) );
        CHECK( !GeneralAI::validVector(  std::vector< float >( {   } ), 1, 1 ) );
    }

    TEST( validVectorOnlyContainsZeros )
    {
        CHECK( GeneralAI::validVector(  std::vector< float >( { 0 } ), 1, 0 ) );
        CHECK( GeneralAI::validVector(  std::vector< float >( { 0 } ), 1, 1 ) );

        CHECK( GeneralAI::validVector(  std::vector< float >( 1, 0 ) , 1, 0 ) );

        CHECK( !GeneralAI::validVector(  std::vector< float >( { 0 } ), 0, 0 ) );
        CHECK( !GeneralAI::validVector(  std::vector< float >( { 0 } ), 0, 1 ) );

        CHECK( !GeneralAI::validVector(  std::vector< float >( { 0 } ), 2, 0 ) );
        CHECK( !GeneralAI::validVector(  std::vector< float >( { 0 } ), 2, 1 ) );
    }
}
