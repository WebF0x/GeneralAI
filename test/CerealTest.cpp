#include "UnitTest++/UnitTest++.h"

#include <fstream>
#include <cereal/archives/binary.hpp>

class Base
{
    public:
        Base() : someConstant(1)
        {
        }

    private:
        const int someConstant;

        friend cereal::access;
        template < class Archive >
        void serialize( Archive & ar )
        {
            ar( const_cast< int & >( someConstant ) );
        }
};

SUITE( CerealTest )
{
    TEST( basicSaveAndLoad )
    {
        const std::string saveFileName = "CerealTest";
        const int expectedData = 42;
        int actualData = 666;

        {
            std::ofstream file( saveFileName, std::ios::binary );
            CHECK( !file.fail() );

            cereal::BinaryOutputArchive archive( file );
            archive( expectedData );
        }

        {
            std::ifstream file( saveFileName, std::ios::binary );
            CHECK( !file.fail() );

            cereal::BinaryInputArchive archive( file );
            archive( actualData );
        }

        CHECK_EQUAL( expectedData, actualData );

        // Delete save file
        CHECK( !remove( saveFileName.data() ) ) ;
    }

    TEST( loadConstantVariable )
    {
        const std::string saveFileName = "CerealTest";
        const int expectedData = 42;
        const int actualData = 666;

        {
            std::ofstream file( saveFileName, std::ios::binary );
            CHECK( !file.fail() );

            cereal::BinaryOutputArchive archive( file );
            archive( expectedData );
        }

        {
            std::ifstream file( saveFileName, std::ios::binary );
            CHECK( !file.fail() );

            cereal::BinaryInputArchive archive( file );
            archive( const_cast< int & >( actualData ) );
        }

        CHECK_EQUAL( expectedData, actualData );

        // Delete save file
        CHECK( !remove( saveFileName.data() ) ) ;
    }
}
