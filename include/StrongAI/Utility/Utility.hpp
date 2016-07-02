bool isAlmostEqual( double a, double b, double absoluteTolerance );
bool isAlmostEqual( float a, float b, float absoluteTolerance );

template< class Container >
bool isAlmostEqual( const Container& containerA, const Container& containerB, double absoluteTolerance )
{
    if( containerA.size() != containerB.size() ) return false;

    auto containerIteratorA = containerA.begin();
    auto containerIteratorB = containerB.begin();

    while( containerIteratorA != containerA.end() )
    {
        if( !isAlmostEqual( *containerIteratorA, *containerIteratorB, absoluteTolerance ) )
        {
            return false;
        }

        containerIteratorA++;
        containerIteratorB++;
    }

    return true;
}

//////////////////
// Class Random //
//////////////////

#include <random> //mt19937_64

class Random
{
    public:
        static double randomProbability();
        static std::mt19937_64& getRandomNumberGenerator();

    private:
        static std::mt19937_64 m_randomNumberGenerator;
};
