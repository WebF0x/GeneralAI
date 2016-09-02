#include "UnitTest++/UnitTest++.h"

#include "AI/HumanAI/HumanAI.hpp"

SUITE( HumanAITest )
{
    TEST( smokeTest )
    {
        HumanAI ai( 0, 0, 0, 0 );
    }
}
