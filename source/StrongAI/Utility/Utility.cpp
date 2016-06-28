#include <algorithm>
#include "StrongAI/Utility/Utility.hpp"

bool isAlmostEqual( double a, double b, double absoluteTolerance )
{
    return std::abs( a - b ) <= std::abs( absoluteTolerance );
}
