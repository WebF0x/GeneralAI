#include <iostream>
#include <map>
#include <ctime>
#include "StrongAI/AI/DarwinAI/DarwinAI.hpp"
#include <cereal/types/memory.hpp>

const int AMPLITUDE = 100;

void manualTesting( std::unique_ptr< NeuralNetAI >& individual )
{
    while( true )
    {
        float in1, in2;
        std::cin >> in1;
        std::cin >> in2;
        std::vector< float > input( { in1, in2 } );

        float out = individual -> output( input ) [ 0 ];
        std::cout << in1 << " + " << in2 << " => " << out << std::endl;
    }
}

class AdderDarwinAI : public DarwinAI
{
    public:
    AdderDarwinAI() : DarwinAI( 2, 1, AMPLITUDE, 2 * AMPLITUDE )
    {

    }

    private:
    // Task: Output the sum of the two inputs
    virtual float fitnessEval( NeuralNetAI& ai )
    {
        float fitness = 0;  // Perfect fitness is 0 ( in this case )

        for( int i = 0; i < 10; i++ )
        {
            float a = GeneralAI::randomProbability() * 100;
            float b = GeneralAI::randomProbability() * 100;
            float sum = a + b;

            std::vector< float > input( { a, b } );

            auto output = ai.output( input );
            float out = output[ 0 ];

            fitness -= abs( out - sum );
        }

        return fitness;
    }
};

int main()
{
    std::cout << "Generating initial population" << std::endl;
    AdderDarwinAI population;

    std::cout << "Population is evolving" << std::endl;
    for( int i = 0; i < 100; i++ )
    {
        std::cout << "\t" << i << " %" << std::endl;
        population.evolve( 100 );
    }

    std::cout << "Saving population" << std::endl;
    // GeneralAI::save< AdderDarwinAI, cereal::JSONOutputArchive > ( AdderDarwinAI, "save.txt" );

    std::cout << "Selecting best individual" << std::endl;
    std::unique_ptr< NeuralNetAI >& champion = population.bestIndividual();

    std::cout << "Manual Testing" << std::endl;
    manualTesting( champion );

    return 0;
}
