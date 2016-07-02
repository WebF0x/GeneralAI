#include "UnitTest++/UnitTest++.h"
#include "StrongAI/Utility/Utility.hpp"

#include <vector>

SUITE( Utility )
{
    TEST( isAlmostEqualReturnsTrueForIdenticalPositiveDoubles )
    {
        const double value = 1.0;
        const double absoluteTolerance = 0.001;
        CHECK( isAlmostEqual( value, value, absoluteTolerance ) );
    }

    TEST( isAlmostEqualReturnsFalseForDifferentPositiveDoubles )
    {
        const double smaller = 1.0;
        const double bigger = 1.002;
        const double absoluteTolerance = 0.001;
        CHECK( !isAlmostEqual( smaller, bigger, absoluteTolerance ) );
    }

    TEST( isAlmostEqualReturnsFalseForOppositeSignsDoubles )
    {
        const double value = 1.0;
        const double absoluteTolerance = 0.001;
        CHECK( !isAlmostEqual( value, -value, absoluteTolerance ) );
    }

    TEST( isAlmostEqualIgnoresToleranceSign )
    {
        const double value = 1.0;
        const double negativeAbsoluteTolerance = -0.001;
        CHECK( isAlmostEqual( value, value, negativeAbsoluteTolerance ) );
    }

    TEST( isAlmostEqualWorksWithFloats )
    {
        const float value = 1.0;
        const float absoluteTolerance = 0.001;
        CHECK( isAlmostEqual( value, value, absoluteTolerance ) );
    }

    TEST( isAlmostEqualWorksWithVectors )
    {
        const std::vector<double> vectorA = {1, 2, 3, 4};
        const std::vector<double> vectorB = {1, 2, 3, 4};
        const double absoluteTolerance = 0.001;

        CHECK( isAlmostEqual( vectorA, vectorB, absoluteTolerance ) );
    }
}
