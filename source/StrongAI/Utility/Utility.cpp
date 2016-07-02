#include <algorithm>
#include "StrongAI/Utility/Utility.hpp"

#include <vector>

bool isAlmostEqual( double a, double b, double absoluteTolerance )
{
    return std::abs( a - b ) <= std::abs( absoluteTolerance );
}

bool isAlmostEqual( const std::vector<double>& containerA, const std::vector<double>& containerB, double absoluteTolerance )
{
    if( containerA.size() != containerB.size() ) return false;

    for( int i = 0; i < containerA.size(); i++ )
    {
        if( !isAlmostEqual( containerA[i], containerB[i], absoluteTolerance ) )
        {
            return false;
        }
    }

    return true;
}
