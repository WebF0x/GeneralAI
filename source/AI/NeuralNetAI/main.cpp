#include <iostream>
#include "AI/NeuralNetAI/NeuralNetAI.hpp"
#include <map>
#include <ctime>
#include "AI/HumanAI/HumanAI.hpp"
#include <cereal/types/memory.hpp>

default_random_engine randomGenerator;
const int AMPLITUDE = 100;
const int NUM_OF_GENERATIONS = 100;
const int POPULATION_SIZE = 100;

// Functions
double fitnessEval( NeuralNetAI& );

void init();

void initPopulation( std::vector< std::unique_ptr< NeuralNetAI > >& population );

// Returns range of fitnessScores ( max - min )
double calculateFitnessScores( std::vector< std::unique_ptr< NeuralNetAI > >& population, std::vector< double >& fitnessScores, double& minFitness, double& maxFitness );

void calculateFitnessScores( std::vector< std::unique_ptr< NeuralNetAI > >& population, std::vector< double >& fitnessScores );

// Update population with a next generation
void createNextGeneration( std::vector< std::unique_ptr< NeuralNetAI > >& population, std::vector< double >& fitnessScores, double minFitness, double maxFitness );

void manualTesting( std::unique_ptr< NeuralNetAI >& individual );

// Return the best individual of the population
// Parameter population cannot be empty
std::unique_ptr< NeuralNetAI >& bestIndividual( std::vector< std::unique_ptr< NeuralNetAI > >& population );

int main()
{
    //*
    std::vector< NeuralNetAI > population;
    population.push_back( NeuralNetAI( 1, 1, 1, 1 ) );
    population.push_back( NeuralNetAI( 1, 1, 1, 1 ) );

    GeneralAI::save< std::vector< NeuralNetAI >, cereal::JSONOutputArchive >( population, "save.txt");

    return 0;

    /*/
    std::cout << "Initializing random number generator" << std::endl;
    init();

    std::cout << "Generating initial population" << std::endl;
    std::vector< std::unique_ptr< NeuralNetAI > > population;


    // std::unique_ptr< NeuralNetAI > bob( new NeuralNetAI( 2, 1, AMPLITUDE, 2 * AMPLITUDE ) );
    std::cout << "Attempting to load" << std::endl;
    if( GeneralAI::load< decltype( population ), cereal::JSONInputArchive>( population, "save.txt") )
    {
        std::cout << "Population loaded" << std::endl;
    }
    else
    {
        std::cout << "Loading failed" << std::endl
            << "Generating random population" << std::endl;
        initPopulation( population );
    }

    /// Evolve a better population over the course of many generations
    for( int i = 0; i < NUM_OF_GENERATIONS; i++ )
    {
        std::cout << NUM_OF_GENERATIONS - i << std::endl;
        std::vector< double > fitnessScores;
        double minFitness, maxFitness;
        calculateFitnessScores( population, fitnessScores, minFitness, maxFitness );
        createNextGeneration( population, fitnessScores, minFitness, maxFitness );
    }

    std::unique_ptr< NeuralNetAI >& champion = bestIndividual( population );

    GeneralAI::save< std::vector< std::unique_ptr< NeuralNetAI > >, cereal::JSONOutputArchive>( population, "save.txt" );

    manualTesting( champion );

    return 0;
    //*/
}

// Returns the fitness of the AI
double fitnessEval( NeuralNetAI& ai )
{
    std::uniform_real_distribution< double > distribution( -AMPLITUDE, AMPLITUDE );

    double fitness = 0;  // Perfect fitness is 0 ( in this case )

    for( int i = 0; i < 10; i++ )
    {
        double in1 = distribution( randomGenerator );
        double in2 = distribution( randomGenerator );
        double somme = in1 + in2;

        std::vector< double > input( { in1, in2 } );

        auto output = ai.output( input );
        double out = output[ 0 ];

        fitness -= abs( out - somme );
    }

    return fitness;
}

void init()
{
    // Random Number Generator
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    randomGenerator = default_random_engine( seed );
}

void initPopulation( std::vector< std::unique_ptr< NeuralNetAI > >& population )
{
    population.clear();

    for( int i = 0; i < POPULATION_SIZE; i++ )
    {
        std::unique_ptr< NeuralNetAI > individual( new NeuralNetAI( 2, 1, AMPLITUDE, 2 * AMPLITUDE ) );
        individual->mutate();
        population.push_back( std::move( individual ) );
    }
}

double calculateFitnessScores( std::vector< std::unique_ptr< NeuralNetAI > >& population, std::vector< double >& fitnessScores, double& minFitness, double& maxFitness )
{
    for( unsigned int i = 0; i < population.size(); i++ )
    {
        double fitness = fitnessEval( *population[ i ] );
        fitnessScores.push_back( fitness );

        if( i == 0 )
        {
            minFitness = fitness;
            maxFitness = fitness;
        }
        else
        {
            if( fitness < minFitness ) minFitness = fitness;
            if( fitness>maxFitness ) maxFitness = fitness;
        }
    }

    return max( Fitness - minFitness );
}

void calculateFitnessScores( std::vector< std::unique_ptr< NeuralNetAI > >& population, std::vector< double >& fitnessScores )
{
    for( unsigned int i = 0; i < population.size(); i++ )
    {
        double fitness = fitnessEval(*population[ i ] );
        fitnessScores.push_back( fitness );
    }
}

void createNextGeneration( std::vector< std::unique_ptr< NeuralNetAI > >& population, std::vector< double >& fitnessScores, double minFitness, double maxFitness )
{
    std::vector< std::unique_ptr< NeuralNetAI > > newPopulation;
    std::vector< bool > parentCloned( POPULATION_SIZE, false );
    while( newPopulation.size() < POPULATION_SIZE )
    {
        // Pick a random individual
        std::uniform_int_distribution< int > distribution( 0, POPULATION_SIZE - 1 );
        int index = distribution( randomGenerator );
        double fitness = fitnessScores.at( index );

        std::uniform_real_distribution< double > distribution0_1( 0, 1 );
        double chance = distribution0_1( randomGenerator );

        if( chance <= ( ( fitness - minFitness ) )/( max( Fitness - minFitness )_ ) ) // Gets picked by the roulette
        {
            if(!parentCloned.at( index ) )  // We want only one parent cloned
            {
                parentCloned.at( index ) = true;

                std::unique_ptr< NeuralNetAI > parent( new NeuralNetAI( *( population.at( index  ) ) ) );
                newPopulation.push_back( std::move( parent ) );
            }

            if( newPopulation.size() < POPULATION_SIZE )  // Can have multiple mutated children
            {
                std::unique_ptr< NeuralNetAI > child( new NeuralNetAI( *( population.at( index ) ) ) );
                child->mutate();
                newPopulation.push_back( std::move( child ) );
            }
        }
    }

    population.clear();
    for( auto it=newPopulation.rbegin(); it!=newPopulation.rend(); it++ )
    {
        population.push_back( std::move(*it ) );
    }
}

void manualTesting( std::unique_ptr< NeuralNetAI >& individual )
{
    std::cout << std::endl
         << "Manual Testing" << std::endl;

    while( true )
    {
        double in1, in2;
        std::cin >> in1;
        std::cin >> in2;
        std::vector< double > input( { in1, in2 } );

        double out = individual->output( input )[ 0 ];
        std::cout << in1 << " + " << in2 << " => " << out << std::endl;
    }
}

std::unique_ptr< NeuralNetAI >& bestIndividual( std::vector< std::unique_ptr< NeuralNetAI > >& population )
{
    std::vector< double > fitnessScores;
    calculateFitnessScores( population, fitnessScores );

    int indexOfBestIndividual = 0;
    double fitnessOfBestIndividual = fitnessScores.at( 0 ) ;

    for( unsigned int i = 1; i < fitnessScores.size(); i++ )
    {
        double fitness = fitnessScores.at( i );
        if( fitness > fitnessOfBestIndividual )
        {
            indexOfBestIndividual = i;
            fitnessOfBestIndividual = fitness;
        }
    }

    return population.at( indexOfBestIndividual );
}

