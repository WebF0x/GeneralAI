#include "StrongAI/AI/DarwinAI/DarwinAI.hpp"

DarwinAI::DarwinAI( int inputSize, int outputSize, int maxInput, int maxOutput, int populationSize )
    : GeneralAI( inputSize, outputSize, maxInput, maxOutput )
{
    initPopulation( populationSize );
}

void DarwinAI::initPopulation( const int populationSize )
{
    m_population.clear();

    for( int i = 0; i < populationSize; i++ )
    {
        NeuralNetAI individual( INPUT_SIZE, OUTPUT_SIZE, INPUT_AMPLITUDE, OUTPUT_AMPLITUDE );
        individual.mutate();
        m_population.push_back( individual );
    }
}

void DarwinAI::evolve( int generations )
{
    /// Evolve a better population over the course of many generations
    for( int i = 0; i < generations; i++ )
    {
        std::vector< float > fitnessScores;
        float minFitness, maxFitness;
        calculateFitnessScores( fitnessScores, minFitness, maxFitness );
        createNextGeneration( fitnessScores, minFitness, maxFitness );
    }
}

float DarwinAI::calculateFitnessScores( std::vector< float >& fitnessScores, float& minFitness, float& maxFitness )
{
    for( unsigned int i = 0; i < m_population.size(); i++ )
    {
        float fitness = fitnessEval( m_population[ i ] );
        fitnessScores.push_back( fitness );

        if( i == 0 )
        {
            minFitness = fitness;
            maxFitness = fitness;
        }
        else
        {
            if( fitness < minFitness ) minFitness = fitness;
            if( fitness > maxFitness ) maxFitness = fitness;
        }
    }

    return maxFitness - minFitness;
}

void DarwinAI::calculateFitnessScores( std::vector< float >& fitnessScores )
{
    for( unsigned int i = 0; i < m_population.size(); i++ )
    {
        float fitness = fitnessEval( m_population[ i ] );
        fitnessScores.push_back( fitness );
    }
}

void DarwinAI::createNextGeneration( std::vector< float >& fitnessScores, float minFitness, float maxFitness )
{
    const int populationSize = m_population.size();
    std::vector< NeuralNetAI > newPopulation;
    std::vector< bool > parentCloned( populationSize, false );
    while( newPopulation.size() < ( unsigned int )populationSize )
    {
        // Pick a random individual
        std::uniform_int_distribution< int > distribution( 0, populationSize - 1 );
        int index = distribution( m_randomNumberGenerator );
        float fitness = fitnessScores.at( index );

        std::uniform_real_distribution< float > distribution0_1( 0, 1 );
        float chance = distribution0_1( m_randomNumberGenerator );

        if( chance <= ( fitness - minFitness ) / ( maxFitness - minFitness ) ) // Gets picked by the roulette
        {
            if( !parentCloned.at( index ) )  // We want only one parent cloned
            {
                parentCloned.at( index ) = true;

                NeuralNetAI parent( m_population.at( index ) );
                newPopulation.push_back( parent );
            }

            if( newPopulation.size() < ( unsigned int )populationSize )  // Can have multiple mutated children
            {
                NeuralNetAI child( m_population.at( index ) );
                child.mutate();
                newPopulation.push_back( child );
            }
        }
    }

    m_population.clear();
    for( auto it = newPopulation.rbegin(); it != newPopulation.rend(); it++ )
    {
        m_population.push_back( *it );
    }

    assert( m_population.size() == populationSize );
}

NeuralNetAI& DarwinAI::bestIndividual()
{
    assert( !m_population.empty() );
    std::vector< float > fitnessScores;
    calculateFitnessScores( fitnessScores );

    int indexOfBestIndividual = 0;
    float fitnessOfBestIndividual = fitnessScores.at( 0 );

    for( unsigned int i = 1; i < fitnessScores.size(); i++ )
    {
        float fitness = fitnessScores.at( i );
        if( fitness > fitnessOfBestIndividual )
        {
            indexOfBestIndividual = i;
            fitnessOfBestIndividual = fitness;
        }
    }

    return m_population.at( indexOfBestIndividual );
}

void DarwinAI::coreLearn( const std::vector< float >& input, const std::vector< float >& output, float outcome )
{
    for( auto& individual : m_population )
    {
        individual.learn( input, output, outcome );
    }
}

std::vector< float > DarwinAI::coreOutput( const std::vector< float >& input )
{
    return bestIndividual().output( input );
}
