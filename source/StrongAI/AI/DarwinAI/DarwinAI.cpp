#include "StrongAI/AI/DarwinAI/DarwinAI.hpp"

DarwinAI::DarwinAI( int inputSize, int outputSize, int maxInput, int maxOutput, int populationSize )
    : GeneralAI( inputSize, outputSize, maxInput, maxOutput ),
    POPULATION_SIZE( populationSize )
{
    initPopulation();
}

void DarwinAI::initPopulation()
{
    m_population.clear();

    for( int i = 0; i < POPULATION_SIZE; i++ )
    {
        std::unique_ptr< NeuralNetAI > individual( new NeuralNetAI( INPUT_SIZE, OUTPUT_SIZE, INPUT_AMPLITUDE, OUTPUT_AMPLITUDE ) );
        individual->mutate();
        m_population.push_back( std::move( individual ) );
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
        float fitness = fitnessEval( *m_population[ i ] );
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
        float fitness = fitnessEval( *m_population[ i ] );
        fitnessScores.push_back( fitness );
    }
}

void DarwinAI::createNextGeneration( std::vector< float >& fitnessScores, float minFitness, float maxFitness )
{
    std::vector< std::unique_ptr< NeuralNetAI > > newPopulation;
    std::vector< bool > parentCloned( POPULATION_SIZE, false );
    while( newPopulation.size() < ( unsigned int )POPULATION_SIZE )
    {
        // Pick a random individual
        std::uniform_int_distribution< int > distribution( 0, POPULATION_SIZE - 1 );
        int index = distribution( m_randomNumberGenerator );
        float fitness = fitnessScores.at( index );

        std::uniform_real_distribution< float > distribution0_1( 0, 1 );
        float chance = distribution0_1( m_randomNumberGenerator );

        if( chance <= ( fitness - minFitness ) / ( maxFitness - minFitness ) ) // Gets picked by the roulette
        {
            if( !parentCloned.at( index ) )  // We want only one parent cloned
            {
                parentCloned.at( index ) = true;

                std::unique_ptr< NeuralNetAI > parent( new NeuralNetAI( *( m_population.at( index ) ) ) );
                newPopulation.push_back( std::move( parent ) );
            }

            if( newPopulation.size() < ( unsigned int )POPULATION_SIZE )  // Can have multiple mutated children
            {
                std::unique_ptr< NeuralNetAI > child( new NeuralNetAI( *( m_population.at( index ) ) ) );
                child->mutate();
                newPopulation.push_back( std::move( child ) );
            }
        }
    }

    m_population.clear();
    for( auto it = newPopulation.rbegin(); it != newPopulation.rend(); it++ )
    {
        m_population.push_back( std::move( *it ) );
    }
}

std::unique_ptr< NeuralNetAI >& DarwinAI::bestIndividual()
{
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
    // Learn
}

std::vector< float > DarwinAI::coreOutput( const std::vector< float >& input )
{
    // Output
    std::vector< float > output( OUTPUT_SIZE );
    return output;
}
