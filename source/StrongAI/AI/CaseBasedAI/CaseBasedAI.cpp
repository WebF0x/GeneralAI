#include "StrongAI/AI/CaseBasedAI/CaseBasedAI.hpp"

using namespace std;

CaseBasedAI::CaseBasedAI( int inputSize, int outputSize, int maxInput, int maxOutput )
    : GeneralAI( inputSize, outputSize, maxInput, maxOutput )
{
}

const std::map< std::vector< float >, std::map< std::vector< float >, float > >& CaseBasedAI::getMemory()
{
    return m_memory;
}

unsigned int CaseBasedAI::getMemorySize()
{
    return getMemory().size();
}

vector< float > CaseBasedAI::coreOutput( const vector< float >& input )
{
    /// Try to recall a similar past experience
    map< vector< float >, map< vector< float >, float > >::iterator pastExperience = m_memory.find( input );

    /// Past experience never seen before
    if( pastExperience == m_memory.end() )
    {
        return randomOutput();
    }

    /// Past experience seen before
    map< vector< float >, float >& reactions = pastExperience->second;
    vector< float > bestKnownOutput = bestOutput( reactions );
    float bestKnownOutcome = reactions.at( bestKnownOutput );

    /**
        To prevent getting stuck in a local maximum:
        bestKnownOutput with the greatest outcome has the best chance to get picked.
        When not picked, returns a randomNewOutput
    **/

    /// Either Repeat previous successful reaction
    if( GeneralAI::randomProbability() < bestKnownOutcome )
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
        catch( runtime_error e )
        {
            // Last decision made must be worth either less than or equal to this bestKnownOutput
            learn( bestKnownOutcome );
            return bestKnownOutput;
        }
    }
}

void CaseBasedAI::coreLearn( const std::vector< float >& input, const std::vector< float >& output, float outcome )
{
    /// Try to recall a similar past experience
    map< vector< float >, map< vector< float >, float > >::iterator pastExperience = m_memory.find( input );

    /// Past experience never seen before
    if( pastExperience == m_memory.end() )
    {
        map< vector< float >, float > newReaction;
        newReaction[ output ] = outcome;
        m_memory[ input ] = newReaction;
        return;
    }

    /// Past experience seen before
    map< vector< float >, float >& reactions = pastExperience->second;
    map< vector< float >, float >::iterator reaction = reactions.find( output );

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

vector< float > CaseBasedAI::randomOutput()
{
    vector< float > output( OUTPUT_SIZE );
    uniform_real_distribution< float > distribution( -OUTPUT_AMPLITUDE, OUTPUT_AMPLITUDE );

    for( int i = 0; i < OUTPUT_SIZE; i++ )
    {
        output[ i ] = distribution( m_randomNumberGenerator );
    }

    return output;
}

vector< float > CaseBasedAI::randomNewOutput( const map< vector< float >, float >& reactions )
{
    vector< float > output;

    do
    {
        output = randomOutput();
    }while( reactions.find( output ) != reactions.end() );  // While output already exists

    return output;
}

vector< float > CaseBasedAI::bestOutput( const map< vector< float >, float >& reactions )
{
    if( reactions.empty() )
    {
        throw length_error( string( " CaseBasedAI::bestOutput()'s parameter is empty" ) );
    }

    vector< vector< float > > bestKnownOutputs;
    bestKnownOutputs.push_back( reactions.begin()->first );
    float bestKnownOutcome =  reactions.begin()->second;

    for ( map< vector< float >, float >::const_iterator it = reactions.begin(); it != reactions.end(); it++ )
    {
        const vector< float >& potentialOutput = it->first;
        float potentialOutcome = it->second;

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
    uniform_int_distribution< int > distribution( 0, bestKnownOutputs.size() - 1 );
    return bestKnownOutputs[ distribution( m_randomNumberGenerator ) ];
}

