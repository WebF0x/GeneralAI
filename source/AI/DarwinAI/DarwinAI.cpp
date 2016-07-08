#include "AI/DarwinAI/DarwinAI.hpp"
#include "Utility/Utility.hpp"

#include <algorithm>

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
        createNextGeneration();
    }
}

/// Evolve the population until the desired fitness is reached
void DarwinAI::evolveToFitness( double desiredFitness )
{
    while( fitness() < desiredFitness )
    {
	evolve();
    }
}

double DarwinAI::fitness()
{
    return fitnessEval( bestIndividual() );
}

std::vector< double > DarwinAI::calculateFitnessScores()
{
    std::vector< double > fitnessScores;
    for( auto& individual : m_population )
    {
        const double fitness = fitnessEval( individual );
        fitnessScores.push_back( fitness );
    }
    return fitnessScores;
}

void DarwinAI::createNextGeneration()
{
    const std::vector< double > reproductionProbabilities = getReproductionProbabilities();

    std::vector< NeuralNetAI > newPopulation;
    while( newPopulation.size() < m_population.size())
    {
        double randomChance  = Random::randomProbability();
        for( int i = 0; i < reproductionProbabilities.size(); i++ )
        {
            double reproductionProbability = reproductionProbabilities.at( i );

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

std::vector< double > DarwinAI::getReproductionProbabilities()
{
    const std::vector< double > fitnessScores = calculateFitnessScores();
    const double minFitness = *std::min_element( fitnessScores.begin(), fitnessScores.end() );

    std::vector< double > fitnessesFromMin;
    for( double fitness : fitnessScores )
    {
        fitnessesFromMin.push_back( fitness - minFitness );
    }
    const double totalFitnessFromMin = std::accumulate( fitnessesFromMin.begin(), fitnessesFromMin.end(), 0.0 );

    std::vector< double > reproductionProbabilities;
    for( double fitnessFromMin : fitnessesFromMin )
    {
        if( totalFitnessFromMin == 0 )
        {
            reproductionProbabilities.push_back( 1 );
        }
        else
        {
            reproductionProbabilities.push_back( fitnessFromMin / totalFitnessFromMin );
        }
    }

    return reproductionProbabilities;
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
    const int randomIndex = distribution( Random::getRandomNumberGenerator() );

    return m_population.at( randomIndex );
}

void DarwinAI::coreLearn( const std::vector< double >& input, const std::vector< double >& output, double outcome )
{
    for( auto& individual : m_population )
    {
        individual.learn( input, output, outcome );
    }
}

std::vector< double > DarwinAI::coreOutput( const std::vector< double >& input )
{
    return bestIndividual().output( input );
}
