#ifndef DARWIN_AI_HPP
#define DARWIN_AI_HPP

#include "AI/NeuralNetAI/NeuralNetAI.hpp"

class DarwinAI : public GeneralAI
{
    public:
        DarwinAI( int inputSize, int outputSize, int maxInput, int maxOutput, int populationSize = 2 );
        void evolve( int generations = 1 );
        void evolveToFitness( double desiredFitness );

        double fitness();

        // Return the best individual of the population
        // Population cannot be empty
        NeuralNetAI& bestIndividual();

        // Return a random individual of the population
        // Population cannot be empty
        NeuralNetAI& randomIndividual();

    private:
        std::vector< double > coreOutput( const std::vector< double >& input );
        void coreLearn( const std::vector< double >& input, const std::vector< double >& output, double outcome );

        void initPopulation( int populationSize );
        virtual double fitnessEval( NeuralNetAI& ai ) = 0;
        std::vector< double > calculateFitnessScores( double& minFitness, double& maxFitness );
        std::vector< double > calculateFitnessScores();

        // Update population with a next generation
        void createNextGeneration( const std::vector< double >& fitnessScores, double minFitness, double maxFitness );

        std::vector< NeuralNetAI > m_population;
        friend cereal::access;
        template < class Archive >
        void serialize( Archive & ar )
        {
            ar( cereal::virtual_base_class< GeneralAI >( this ) );
            ar( m_population );
        }
};


#endif // DARWIN_AI_HPP
