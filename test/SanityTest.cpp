#include "UnitTest++/UnitTest++.h"

#include <vector>
#include <exception>

SUITE( SanityTest )
{
    TEST( check )
    {
        CHECK( true );
    }

    TEST( checkEqual )
    {
        const int expected = 42;
        const int actual = 42;

        CHECK_EQUAL( expected, actual );
    }

    TEST( checkClose )
    {
        const double expected = 10;
        const double actual = 9.9;
        const double tolerance = 0.1;

        CHECK_CLOSE( expected, actual, tolerance );
    }

    TEST( checkArrayEqual )
    {
        const std::vector< int > expected( { 1, 2, 3, 4 } );
        const std::vector< int > actual( { 1, 2, 3, 4 } );
        const int length = 4;

        CHECK_ARRAY_EQUAL( expected, actual, length );
    }

    TEST( checkArrayClose )
    {
        const std::vector< double > expected ( { 1  , 2  , 3  , 4 } );
        const std::vector< double > actual   ( { 1.1, 2.1, 2.9, 3.9 } );
        const int length = 4;
        const double tolerance = 0.1;

        CHECK_ARRAY_CLOSE( expected, actual, length, tolerance );
    }

    TEST( checkArray2DClose )
    {
        std::vector< std::vector< double > > expected;
        expected.push_back( { 1.10, 1.20, 1.30 } );
        expected.push_back( { 2.10, 2.20, 2.30 } );

        std::vector< std::vector< double > > actual;
        actual.push_back( { 1.11, 1.21, 1.31 } );
        actual.push_back( { 2.09, 2.19, 2.29 } );

        const int rows          = 2;
        const int columns       = 3;
        const double tolerance   = 0.1;

        CHECK_ARRAY2D_CLOSE( expected, actual, rows, columns, tolerance );
    }

    TEST( checkThrow )
    {
        CHECK_THROW( throw std::exception(), std::exception );
    }
}
