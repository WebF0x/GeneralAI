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

/// Evolve the population for multiple generations
void DarwinAI::evolve( int generations )
{
    for( int i = 0; i < generations; i++ )
    {
        float minFitness, maxFitness;
        const std::vector< float > fitnessScores = calculateFitnessScores( minFitness, maxFitness );
        createNextGeneration( fitnessScores, minFitness, maxFitness );
    }
}

/// Evolve the population until the desired fitness is reached
void DarwinAI::evolveToFitness( float desiredFitness )
{
    while( fitness() < desiredFitness )
    {
        float minFitness, maxFitness;
        const std::vector< float > fitnessScores = calculateFitnessScores( minFitness, maxFitness );
        createNextGeneration( fitnessScores, minFitness, maxFitness );
    }
}

float DarwinAI::fitness()
{
    return fitnessEval( bestIndividual() );
}

std::vector< float > DarwinAI::calculateFitnessScores( float& minFitness, float& maxFitness )
{
    std::vector< float > fitnessScores;
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
            minFitness = std::min( fitness, minFitness );
            maxFitness = std::max( fitness, maxFitness );
        }
    }
    return fitnessScores;
}

std::vector< float > DarwinAI::calculateFitnessScores()
{
    std::vector< float > fitnessScores;
    for( auto& individual : m_population )
    {
        float fitness = fitnessEval( individual );
        fitnessScores.push_back( fitness );
    }
    return fitnessScores;
}

void DarwinAI::createNextGeneration( const std::vector< float >& fitnessScores, float minFitness, float maxFitness )
{
    float totalFitnessGreaterThanMinimum = 0;
    for( auto fitness : fitnessScores )
    {
        float fitnessGreaterThanMinimum = fitness - minFitness;
        totalFitnessGreaterThanMinimum += fitnessGreaterThanMinimum;
    }

    std::vector< float > reproductionProbabilities;
    for( auto fitness : fitnessScores )
    {
        float reproductionProbability = ( totalFitnessGreaterThanMinimum != 0 ) ? ( ( fitness - minFitness) / totalFitnessGreaterThanMinimum ) : 1;
        reproductionProbabilities.push_back( reproductionProbability );
    }

    std::vector< NeuralNetAI > newPopulation;
    while( newPopulation.size() < m_population.size())
    {
        float randomChance  = randomProbability();
        for( int i = 0; i < reproductionProbabilities.size(); i++ )
        {
            float reproductionProbability = reproductionProbabilities.at( i );

            if( randomChance <= reproductionProbability)
            {
                NeuralNetAI clonedIndividual( m_population.at( i ) );

                // Keep the original individual
                newPopulation.push_back( clonedIndividual );

                // Keep a mutation of the individual ( if there is enough room )
                if( newPopulation.size() < m_population.size() )
                {
                    clonedIndividual.mutate();
                    newPopulation.push_back( clonedIndividual );
                }
            }
            else
            {
                randomChance += reproductionProbability;
            }
        }
    }

    m_population = std::vector< NeuralNetAI >( newPopulation );
}

NeuralNetAI& DarwinAI::bestIndividual()
{
    assert( !m_population.empty() );

    const auto fitnessScores = calculateFitnessScores();
    const auto bestFitnessScore = std::max_element( fitnessScores.begin(), fitnessScores.end() );
    const auto indexOfBestIndividual = std::distance( fitnessScores.begin(), bestFitnessScore );
    return m_population.at( indexOfBestIndividual );
}

NeuralNetAI& DarwinAI::randomIndividual()
{
    assert( !m_population.empty() );

    std::uniform_int_distribution< int > distribution( 0, m_population.size() );
    const int randomIndex = distribution( GeneralAI::m_randomNumberGenerator );

    return m_population.at( randomIndex );
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
