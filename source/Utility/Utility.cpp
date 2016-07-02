#include <algorithm>
#include "Utility/Utility.hpp"

bool isAlmostEqual( double a, double b, double absoluteTolerance )
{
    return std::abs( a - b ) <= std::abs( absoluteTolerance );
}

bool isAlmostEqual( float a, float b, float absoluteTolerance )
{
    return isAlmostEqual( double(a), double(b), double(absoluteTolerance) );
}

//////////////////
// Class Random //
//////////////////

// To do: Seed the random number generator with a random_device when it's implemented ( *wink wink GCC* )
std::mt19937_64 Random::m_randomNumberGenerator( time( 0 ) );

std::mt19937_64& Random::getRandomNumberGenerator()
{
    return m_randomNumberGenerator;
}

// Returns a random double in [ 0, 1 ]
double Random::randomProbability()
{
    std::uniform_real_distribution< double > distribution( 0, 1 );
    return distribution( m_randomNumberGenerator );
}
