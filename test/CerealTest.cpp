#include "UnitTest++/UnitTest++.h"

#include <fstream>
#include <cereal/archives/binary.hpp>

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
}
