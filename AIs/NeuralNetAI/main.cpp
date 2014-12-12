#include <iostream>
#include "NeuralNetAI.h"
#include <map>
#include <ctime>
#include "../HumanAI/HumanAI.h"

using namespace std;

default_random_engine randomGenerator;
const int AMPLITUDE = 100;
const int NUM_OF_GENERATIONS = 9000;
const int POPULATION_SIZE = 100;

//Functions
float fitnessEval(NeuralNetAI& ai);

void init();

void initPopulation(vector<unique_ptr<NeuralNetAI>>& population);

//Returns range of fitnessScores (max-min)
float calculateFitnessScores(vector<unique_ptr<NeuralNetAI>>& population, vector<float>& fitnessScores, float& minFitness, float& maxFitness);

void calculateFitnessScores(vector<unique_ptr<NeuralNetAI>>& population, vector<float>& fitnessScores);

//Update population with a next generation
void createNextGeneration(vector<unique_ptr<NeuralNetAI>>& population, vector<float>& fitnessScores, float minFitness, float maxFitness);

void manualTesting(unique_ptr<NeuralNetAI>& individual);

//Return the best individual of the population
//Parameter population cannot be empty
unique_ptr<NeuralNetAI>& bestIndividual(vector<unique_ptr<NeuralNetAI>>& population);

int main()
{
    init();

    vector<unique_ptr<NeuralNetAI>> population;
    initPopulation(population);

    ///Evolve a better population over the course of many generations
    for(int i=0;i<NUM_OF_GENERATIONS;++i)
    {
        cout<<NUM_OF_GENERATIONS-i<<endl;
        vector<float> fitnessScores;
        float minFitness, maxFitness;
        calculateFitnessScores(population, fitnessScores, minFitness, maxFitness);
        createNextGeneration(population, fitnessScores, minFitness, maxFitness);
    }

    manualTesting(bestIndividual(population));

    return 0;
}

//Returns the fitness of the AI
float fitnessEval(NeuralNetAI& ai)
{
    uniform_real_distribution<float> distribution(-AMPLITUDE, AMPLITUDE);

    float fitness = 0;  //Perfect fitness is 0 (in this case)

    for(int i=0; i<10; ++i)
    {
        float in1 = distribution(randomGenerator);
        float in2 = distribution(randomGenerator);
        float somme = in1+in2;

        vector<float> input({in1,in2});

        auto output = ai.output(input);
        float out = output[0];

        fitness -= abs(out-somme);
    }

    return fitness;
}

void init()
{
    //Random Number Generator
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    randomGenerator = default_random_engine(seed);
}

void initPopulation(vector<unique_ptr<NeuralNetAI>>& population)
{
    population.clear();

    for(int i=0;i<POPULATION_SIZE; ++i)
    {
        unique_ptr<NeuralNetAI> individual(new NeuralNetAI(2,1,AMPLITUDE,2*AMPLITUDE));
        individual->mutate();
        population.push_back(move(individual));
    }
}

float calculateFitnessScores(vector<unique_ptr<NeuralNetAI>>& population, vector<float>& fitnessScores, float& minFitness, float& maxFitness)
{
    for(unsigned int i=0; i<population.size(); ++i)
    {
        float fitness = fitnessEval(*population[i]);
        fitnessScores.push_back(fitness);

        if(i==0)
        {
            minFitness = fitness;
            maxFitness = fitness;
        }
        else
        {
            if(fitness<minFitness) minFitness = fitness;
            if(fitness>maxFitness) maxFitness = fitness;
        }
    }

    return maxFitness-minFitness;
}

void calculateFitnessScores(vector<unique_ptr<NeuralNetAI>>& population, vector<float>& fitnessScores)
{
    for(unsigned int i=0; i<population.size(); ++i)
    {
        float fitness = fitnessEval(*population[i]);
        fitnessScores.push_back(fitness);
    }
}

void createNextGeneration(vector<unique_ptr<NeuralNetAI>>& population, vector<float>& fitnessScores, float minFitness, float maxFitness)
{
    vector<unique_ptr<NeuralNetAI>> newPopulation;
    vector<bool> parentCloned(POPULATION_SIZE, false);
    while(newPopulation.size() < POPULATION_SIZE)
    {
        //Pick a random individual
        uniform_int_distribution<int> distribution(0, POPULATION_SIZE - 1);
        int index = distribution(randomGenerator);
        float fitness = fitnessScores.at(index);

        uniform_real_distribution<float> distribution0_1(0,1);
        float chance = distribution0_1(randomGenerator);

        if(chance <= (fitness-minFitness)/(maxFitness-minFitness) ) //Gets picked by the roulette
        {
            if(!parentCloned.at(index))  //We want only one parent cloned
            {
                parentCloned.at(index) = true;

                unique_ptr<NeuralNetAI> parent(new NeuralNetAI(*(population.at(index))));
                newPopulation.push_back(move(parent));
            }

            if(newPopulation.size() < POPULATION_SIZE)  //Can have multiple mutated children
            {
                unique_ptr<NeuralNetAI> child(new NeuralNetAI(*(population.at(index))));
                child->mutate();
                newPopulation.push_back(move(child));
            }
        }
    }

    population.clear();
    for(auto it=newPopulation.rbegin(); it!=newPopulation.rend(); ++it)
    {
        population.push_back(move(*it));
    }
}

void manualTesting(unique_ptr<NeuralNetAI>& individual)
{
    cout<<endl
        <<"Manual Testing"<<endl;

    while(true)
    {
        float in1,in2;
        cin>>in1;
        cin>>in2;
        vector<float> input({in1,in2});

        float out = individual->output(input)[0];
        cout<<in1<<" + "<<in2<<" => "<<out<<endl;
    }
}

unique_ptr<NeuralNetAI>& bestIndividual(vector<unique_ptr<NeuralNetAI>>& population)
{
    vector<float> fitnessScores;
    calculateFitnessScores(population, fitnessScores);

    int indexOfBestIndividual = 0;
    float fitnessOfBestIndividual = fitnessScores.at(0);

    for(unsigned int i=1; i<fitnessScores.size(); ++i)
    {
        float fitness = fitnessScores.at(i);
        if(fitness > fitnessOfBestIndividual)
        {
            indexOfBestIndividual = i;
            fitnessOfBestIndividual = fitness;
        }
    }

    return population.at(indexOfBestIndividual);
}

