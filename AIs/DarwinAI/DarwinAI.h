#ifndef DARWINAI_H_INCLUDED
#define DARWINAI_H_INCLUDED

#include "../NeuralNetAI/NeuralNetAI.h"

class DarwinAI : public GeneralAI
{
    public:
        DarwinAI(int inputSize, int outputSize, int maxInput, int maxOutput);
        void evolve(int generations);

        virtual float fitnessEval(NeuralNetAI& ai) = 0;

        //Returns range of fitnessScores (max-min)
        float calculateFitnessScores(vector<unique_ptr<NeuralNetAI>>& population, vector<float>& fitnessScores, float& minFitness, float& maxFitness);

        void calculateFitnessScores(vector<unique_ptr<NeuralNetAI>>& population, vector<float>& fitnessScores);

        //Update population with a next generation
        void createNextGeneration(vector<unique_ptr<NeuralNetAI>>& population, vector<float>& fitnessScores, float minFitness, float maxFitness);

        //Return the best individual of the population
        //Parameter population cannot be empty
        unique_ptr<NeuralNetAI>& bestIndividual(vector<unique_ptr<NeuralNetAI>>& population);

    private:
        vector<unique_ptr<NeuralNetAI>> m_population;

        const int POPULATION_SIZE;

        void initPopulation();

        std::vector<float> coreOutput(const std::vector<float>& input);
        void coreLearn(const std::vector<float>& input, const std::vector<float>& output, float outcome);

        friend cereal::access;
        template <class Archive>
        void serialize( Archive & ar )
        {
            ar( cereal::virtual_base_class<GeneralAI>(this) );

            /**
                You can serialize any variables that you want like this:
                    ar( cereal::virtual_base_class<GeneralAI>(this), var1, var2, varN );
            **/
        }
};


#endif // DARWINAI_H_INCLUDED
