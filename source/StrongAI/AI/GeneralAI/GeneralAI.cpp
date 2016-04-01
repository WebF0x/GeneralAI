#include "StrongAI/AI/GeneralAI/GeneralAI.hpp"

// To do: Seed the random number generator with a random_device when it's implemented ( *wink wink GCC* )
std::mt19937_64 GeneralAI::m_randomNumberGenerator( time( NULL ) );  // Shared random number generator

GeneralAI::GeneralAI( const int inputSize, const int outputSize, const int inputAmplitude, const int outputAmplitude ) :
    INPUT_SIZE( inputSize ), OUTPUT_SIZE( outputSize ), INPUT_AMPLITUDE( inputAmplitude ), OUTPUT_AMPLITUDE( outputAmplitude )
{
    if( INPUT_SIZE          < 0 ) throw std::out_of_range( std::string ( "negative INPUT_SIZE" ) );
    if( OUTPUT_SIZE         < 0 ) throw std::out_of_range( std::string ( "negative OUTPUT_SIZE" ) );
    if( INPUT_AMPLITUDE     < 0 ) throw std::out_of_range( std::string ( "negative INPUT_AMPLITUDE" ) );
    if( OUTPUT_AMPLITUDE    < 0 ) throw std::out_of_range( std::string ( "negative OUTPUT_AMPLITUDE" ) );
}

void GeneralAI::learn( const std::vector< float >& input, const std::vector< float >& output, const float outcome )
{
    /// Check parameters validity
    if( !validInput( input ) )
    {
        throw std::length_error( std::string( "invalid input" ) );
    }

    if( !validOutput( output ) )
    {
        throw std::length_error( std::string( "invalid output" ) );
    }

    if( !validOutcome( outcome ) )
    {
        throw std::length_error( std::string( "invalid outcome" ) );
    }

    /// Learn lesson
    coreLearn( input, output, outcome );

    /// Short - term memory
    m_lastLesson = std::make_tuple( input, output, outcome );
    m_lastLessonEnabled = true;
}

void GeneralAI::learn( const std::tuple< std::vector< float >, std::vector< float >, float >& lesson )
{
    auto& input     = std::get< 0 >( lesson );
    auto& output    = std::get< 1 >( lesson );
    auto& outcome   = std::get< 2 >( lesson );

    learn( input, output, outcome );
}

void GeneralAI::learn( const std::pair< std::vector< float >, std::vector< float > >& decision, float outcome )
{
    auto& input     = decision.first;
    auto& output    = decision.second;

    learn( input, output, outcome );
}

void GeneralAI::learn( const float outcome )
{
    if( m_lastDecisionEnabled ) // m_lastDecision is not undefined
    {
        learn( m_lastDecision, outcome );
    }
}

std::vector< float > GeneralAI::output()
{
    const std::vector< float > defaultInput( INPUT_SIZE, 0 );
    return output( defaultInput );
}

std::vector< float > GeneralAI::output( const std::vector< float >& input )
{
    /// Check parameters validity
    if( !validInput( input ) )
    {
        throw std::length_error( std::string( "invalid input" ) );
    }

    const std::vector< float > output = coreOutput( input );

    if( !validOutput( output ) )
    {
        throw std::length_error( std::string( "invalid output" ) );
    }

    /// Remember the last decision made
    m_lastDecision = std::make_pair( input, output );
    m_lastDecisionEnabled = true;

    return output;
}

void GeneralAI::reset()
{
    m_lastDecisionEnabled = false;
}

std::pair< std::vector< float >, std::vector< float > > GeneralAI::lastDecision() const
{
    if( !m_lastDecisionEnabled )
    {
        throw std::logic_error( std::string( "m_lastDecisionEnabled == false" ) );
    }

    return m_lastDecision;
}

std::tuple< std::vector< float >, std::vector< float >, float > GeneralAI::lastLesson() const
{
    if( !m_lastLessonEnabled )
    {
        throw std::logic_error( std::string( "GeneralAI::m_lastLessonLearnedEnabled == false") );
    }

    return m_lastLesson;
}

bool GeneralAI::validVector( const std::vector< float >& myvector, const unsigned int size, const int amplitude )
{
    if( myvector.size() != size )
    {
        return false;
    }

    for( unsigned int i = 0; i < myvector.size(); i++ )
    {
        if( !( - amplitude <= myvector[ i ] && myvector[ i ] <= amplitude ) )
        {
            return false;
        }
    }

    return true;
}

bool GeneralAI::validInput( const std::vector< float >& input ) const
{
    return validVector( input, ( unsigned int )INPUT_SIZE, INPUT_AMPLITUDE );
}

bool GeneralAI::validOutput( const std::vector< float >& output ) const
{
    return validVector( output, ( unsigned int )OUTPUT_SIZE, OUTPUT_AMPLITUDE );
}

bool GeneralAI::validOutcome( const float outcome )
{
    return ( -1.f <= outcome && outcome <= 1.f );
}

/**
*   Returns a random float in [ 0, 1 ]
**/
float GeneralAI::randomProbability()
{
    std::uniform_real_distribution< float > distribution( 0, 1 );
    return distribution( m_randomNumberGenerator );
}
