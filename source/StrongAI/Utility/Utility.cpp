#include <algorithm>
#include "StrongAI/Utility/Utility.hpp"

bool isAlmostEqual( double a, double b, double absoluteTolerance )
{
    return std::abs( a - b ) <= std::abs( absoluteTolerance );
}

bool isAlmostEqual( float a, float b, float absoluteTolerance )
{
    return isAlmostEqual( double(a), double(b), double(absoluteTolerance) );
}
