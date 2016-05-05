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
}
