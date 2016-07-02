#include "StrongAI/AI/CaseBasedAI/CaseBasedAI.hpp"
#include "StrongAI/Utility/Utility.hpp"

CaseBasedAI::CaseBasedAI( int inputSize, int outputSize, int maxInput, int maxOutput )
    : GeneralAI( inputSize, outputSize, maxInput, maxOutput )
{
}

const std::map< std::vector< double >, std::map< std::vector< double >, double > >& CaseBasedAI::getMemory()
{
    return m_memory;
}

unsigned int CaseBasedAI::getMemorySize()
{
    return getMemory().size();
}

std::vector< double > CaseBasedAI::coreOutput( const std::vector< double >& input )
{
    /// Try to recall a similar past experience
    std::map< std::vector< double >, std::map< std::vector< double >, double > >::iterator pastExperience = m_memory.find( input );

    /// Past experience never seen before
    if( pastExperience == m_memory.end() )
    {
        return randomOutput();
    }

    /// Past experience seen before
    std::map< std::vector< double >, double >& reactions = pastExperience->second;
    std::vector< double > bestKnownOutput = bestOutput( reactions );
    double bestKnownOutcome = reactions.at( bestKnownOutput );

    /**
        To prevent getting stuck in a local maximum:
        bestKnownOutput with the greatest outcome has the best chance to get picked.
        When not picked, returns a randomNewOutput
    **/

    /// Either Repeat previous successful reaction
    if( Random::randomProbability() < bestKnownOutcome )
    {
        return bestKnownOutput;
    }
    /// Or Try something new
    else
    {
        try
        {
            return randomNewOutput( reactions );
        }
        // Not a single new output exists
        catch( std::runtime_error e )
        {
            // Last decision made must be worth either less than or equal to this bestKnownOutput
            learn( bestKnownOutcome );
            return bestKnownOutput;
        }
    }
}

void CaseBasedAI::coreLearn( const std::vector< double >& input, const std::vector< double >& output, double outcome )
{
    /// Try to recall a similar past experience
    std::map< std::vector< double >, std::map< std::vector< double >, double > >::iterator pastExperience = m_memory.find( input );

    /// Past experience never seen before
    if( pastExperience == m_memory.end() )
    {
        std::map< std::vector< double >, double > newReaction;
        newReaction[ output ] = outcome;
        m_memory[ input ] = newReaction;
        return;
    }

    /// Past experience seen before
    std::map< std::vector< double >, double >& reactions = pastExperience->second;
    std::map< std::vector< double >, double >::iterator reaction = reactions.find( output );

    /// Output never seen before
    if( reaction == reactions.end() )
    {
        reactions.emplace( output, outcome );
        return;
    }

    /// Output seen before
    /*
    *   The outcome can only decrease.
    *   Why: Let's say we play we play chess. I make a move. My opponent could checkmate me but makes a mistake and doesn't and I win. I recall my move as a good move.
    *       The next time this situation presents itself, the opponent plays the checkmate and wins.
    *       The correct reaction is to forget the last time I was lucky and remember that my move can get me checkmated. Doing this move is as bad as losing.
    */
    if( outcome < reactions.at( output ) )
    {
        reactions.at( output ) = outcome;
    }
}

std::vector< double > CaseBasedAI::randomOutput()
{
    std::vector< double > output( OUTPUT_SIZE );
    std::uniform_real_distribution< double > distribution( -OUTPUT_AMPLITUDE, OUTPUT_AMPLITUDE );

    for( int i = 0; i < OUTPUT_SIZE; i++ )
    {
        output[ i ] = distribution( Random::getRandomNumberGenerator() );
    }

    return output;
}

std::vector< double > CaseBasedAI::randomNewOutput( const std::map< std::vector< double >, double >& reactions )
{
    std::vector< double > output;

    do
    {
        output = randomOutput();
    }while( reactions.find( output ) != reactions.end() );  // While output already exists

    return output;
}

std::vector< double > CaseBasedAI::bestOutput( const std::map< std::vector< double >, double >& reactions )
{
    if( reactions.empty() )
    {
        throw std::length_error( std::string( " CaseBasedAI::bestOutput()'s parameter is empty" ) );
    }

    std::vector< std::vector< double > > bestKnownOutputs;
    bestKnownOutputs.push_back( reactions.begin()->first );
    double bestKnownOutcome =  reactions.begin()->second;

    for ( std::map< std::vector< double >, double >::const_iterator it = reactions.begin(); it != reactions.end(); it++ )
    {
        const std::vector< double >& potentialOutput = it->first;
        double potentialOutcome = it->second;

        if( fabs( potentialOutcome - bestKnownOutcome ) < .00000000001f )
        {
            bestKnownOutputs.push_back( potentialOutput );
        }
        else if( potentialOutcome > bestKnownOutcome )
        {
            bestKnownOutputs.clear();
            bestKnownOutputs.push_back( potentialOutput );
            bestKnownOutcome = potentialOutcome;
        }
    }

    /// Return one of the bestKnownOutputs at random
    std::uniform_int_distribution< int > distribution( 0, bestKnownOutputs.size() - 1 );
    return bestKnownOutputs[ distribution( Random::getRandomNumberGenerator() ) ];
}

