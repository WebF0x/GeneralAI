#ifndef DARWIN_AI_HPP
#define DARWIN_AI_HPP

#include "StrongAI/AI/NeuralNetAI/NeuralNetAI.hpp"

class DarwinAI : public GeneralAI
{
    public:
        DarwinAI( int inputSize, int outputSize, int maxInput, int maxOutput, int populationSize = 2 );
        void initPopulation( int populationSize );
        void evolve( int generations );

        virtual float fitnessEval( NeuralNetAI& ai ) = 0;

        //Returns range of fitnessScores ( max-min )
        float calculateFitnessScores( std::vector< float >& fitnessScores, float& minFitness, float& maxFitness );

        void calculateFitnessScores( std::vector< float >& fitnessScores );

        //Update population with a next generation
        void createNextGeneration( std::vector< float >& fitnessScores, float minFitness, float maxFitness );

        //Return the best individual of the population
        //Parameter population cannot be empty
        NeuralNetAI& bestIndividual();

        std::vector< NeuralNetAI > m_population;

    private:
        std::vector< float > coreOutput( const std::vector< float >& input );
        void coreLearn( const std::vector< float >& input, const std::vector< float >& output, float outcome );

        friend cereal::access;
        template < class Archive >
        void serialize( Archive & ar )
        {
            ar( cereal::virtual_base_class< GeneralAI >( this ) );
            ar( m_population );
        }
};


#endif // DARWIN_AI_HPP
