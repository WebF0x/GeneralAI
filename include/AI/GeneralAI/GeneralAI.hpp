#ifndef GENERAL_AI_HPP
#define GENERAL_AI_HPP

//Serialization
#include <fstream>
#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/xml.hpp>

/**
*   Abstract class for general artificial intelligence systems
*
*   Design pattern: Non-Virtual Interface
**/
class GeneralAI// : public SaveSystem
{
    public:
        const int INPUT_SIZE, OUTPUT_SIZE, INPUT_AMPLITUDE, OUTPUT_AMPLITUDE;

        GeneralAI( int inputSize, int outputSize, int inputAmplitude, int outputAmplitude );
        virtual ~GeneralAI() {}

        /// Returns AI's output
        std::vector< double > output();
        std::vector< double > output( const std::vector< double >& input );

        /**
        *   Learn the outcome of output( input )
        *
        *   Worst outcome: -1.f
        *   Best outcome :  1.f
        **/
        void learn( const std::vector< double >& input, const std::vector< double >& output, double outcome );
        void learn( const std::tuple< std::vector< double >, std::vector< double >, double>& lesson );
        void learn( const std::pair< std::vector< double >,std::vector< double > >& decision, double outcome );
        void learn( double outcome );  /// Learn the outcome of the lastDecision

        std::pair < std::vector< double >, std::vector< double > >       lastDecision() const;
        std::tuple< std::vector< double >, std::vector< double >, double > lastLesson() const;
        void reset();

        bool validInput( const std::vector< double >& input ) const;
        bool validOutput( const std::vector< double >& output ) const;
        static bool validOutcome( double outcome );

        ///Serialization ( save/load )
        template< class Object, class Archive = cereal::BinaryOutputArchive >
        static bool save( const Object& obj, const std::string& fileName )
        {
            std::ofstream file( fileName, std::ios::binary );
            if( file.fail() ) return false;

            Archive archive( file );
            archive( cereal::make_nvp( "Object",  obj ) );

            return true;
        }

        template< class Object, class Archive = cereal::BinaryInputArchive >
        static bool load( Object& obj, const std::string& fileName )
        {
            std::ifstream file( fileName, std::ios::binary );
            if( file.fail() ) return false;

            Archive archive( file );
            archive( cereal::make_nvp( "Object",  obj ) );

            return true;
        }

        static bool validVector( const std::vector< double >& v, unsigned int size, int amplitude );

    private:
        //Serialization
        /*
        *   Copy/paste this method in subclasses
        *
        *   Use this format:
        *       ar( cereal::virtual_base_class< Base >( this ), member1, member2, ...);
        */
        friend cereal::access;
        template < class Archive >
        void serialize( Archive & ar )
        {
            ar( cereal::make_nvp( "Input size"        , const_cast< int & >( INPUT_SIZE ) ) );
            ar( cereal::make_nvp( "Output size"       , const_cast< int & >( OUTPUT_SIZE ) ) );
            ar( cereal::make_nvp( "Input amplitude"   , const_cast< int & >( INPUT_AMPLITUDE ) ) );
            ar( cereal::make_nvp( "Output amplitude"  , const_cast< int & >( OUTPUT_AMPLITUDE ) ) );
        }

        /// Subclasses must implement these methods
        virtual void coreLearn( const std::vector< double >& input, const std::vector< double >& output, double outcome ) = 0;
        virtual std::vector< double > coreOutput( const std::vector< double >& input ) = 0;

        /// Short-term memory
        /*
        *   Should this be covered in GeneralAI or the worlds should take care of it?
        *   This is useless overhead for some AI's
        */
        std::pair< std::vector< double >,std::vector< double > > m_lastDecision;
        std::tuple< std::vector< double >, std::vector< double >, double > m_lastLesson;
        bool m_lastDecisionEnabled = false;
        bool m_lastLessonEnabled = false;
};

#endif // GENERAL_AI_HPP
