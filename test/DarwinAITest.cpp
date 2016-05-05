#include "UnitTest++/UnitTest++.h"

#include "StrongAI/AI/DarwinAI/DarwinAI.hpp"

class MyDarwinAI : public DarwinAI
{
    public:
        MyDarwinAI() :
            DarwinAI( 0, 1, 0, 1 )
        {
        }

        //Select for highest output
        float fitnessEval( NeuralNetAI& ai )
        {
            return ai.output().at( 0 );
        };

    private:
        friend cereal::access;
        template < class Archive >
        void serialize( Archive & ar )
        {
            ar( cereal::virtual_base_class< GeneralAI >( this ) );
        }
};

SUITE( DarwinAITest )
{
    TEST( smokeTest )
    {
        std::unique_ptr< DarwinAI > ai( new MyDarwinAI() );

        auto output = ai->output();
        CHECK_EQUAL( 1, output.size() );

        ai->learn( 1 );
    }

    TEST( saveAndLoad )
    {
        const std::string saveFileName = "MyDarwinAI.save";

        MyDarwinAI originalAI;
        MyDarwinAI cloneAI;

        GeneralAI::save< MyDarwinAI >( originalAI, saveFileName );
        GeneralAI::load< MyDarwinAI >( cloneAI,    saveFileName );

        const auto originalOutput = originalAI.output().front();
        const auto cloneOutput    = cloneAI.output().front();
        const double tolerance    = 0.01;
        CHECK_CLOSE( originalOutput, cloneOutput, tolerance );

        // Delete save file
        CHECK( !remove( saveFileName.data() ) ) ;
    }
}
