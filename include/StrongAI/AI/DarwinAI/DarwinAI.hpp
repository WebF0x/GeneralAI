#ifndef DARWIN_AI_HPP
#define DARWIN_AI_HPP

#include "StrongAI/AI/NeuralNetAI/NeuralNetAI.hpp"
#include <algorithm>

class DarwinAI : public GeneralAI
{
    public:
        DarwinAI( int inputSize, int outputSize, int maxInput, int maxOutput, int populationSize = 2 );
        void evolve( int generations );
        void evolveToFitness( float desiredFitness );

        float fitness();

        // Return the best individual of the population
        // Population cannot be empty
        NeuralNetAI& bestIndividual();

        // Return a random individual of the population
        // Population cannot be empty
        NeuralNetAI& randomIndividual();

    private:
        std::vector< float > coreOutput( const std::vector< float >& input );
        void coreLearn( const std::vector< float >& input, const std::vector< float >& output, float outcome );

        void initPopulation( int populationSize );
        virtual float fitnessEval( NeuralNetAI& ai ) = 0;
        std::vector< float > calculateFitnessScores( float& minFitness, float& maxFitness );
        std::vector< float > calculateFitnessScores();

        // Update population with a next generation
        void createNextGeneration( const std::vector< float >& fitnessScores, float minFitness, float maxFitness );

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
