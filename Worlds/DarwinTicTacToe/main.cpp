#include <iostream>
#include <fstream>
#include "../../AIs/NeuralNetAI/NeuralNetAI.h"
#include <map>
#include <ctime>
#include "TicTacToe.h"
#include "TicTacToeHuman.h"
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>

using namespace std;

default_random_engine randomGenerator;
const int AMPLITUDE = 100;
const int NUM_OF_GENERATIONS = 100;
const int POPULATION_SIZE = 100;
const std::string& SAVE_FILE_NAME = "population.save";

//Functions
float fitnessEval(NeuralNetAI& ai);

void init();

void initPopulation(vector<unique_ptr<NeuralNetAI>>& population);

void savePopulation(const vector<unique_ptr<NeuralNetAI>>& population);

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
    initRandom();

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

    savePopulation(population);

    manualTesting(bestIndividual(population));

    return 0;
}

//Returns the fitness of the AI
float fitnessEval(unique_ptr<NeuralNetAI>& ai, vector<unique_ptr<NeuralNetAI>>& population)
{
    TicTacToe game;
    float score = 0;
    const int NUM_OF_GAMES = 1;

    for(int i=0;i<NUM_OF_GAMES; ++i)
    {
        int randomIndex;
        do
        {
            uniform_int_distribution<int> distribution(0,population.size());
            randomIndex = distribution(GeneralAI::m_randomNumberGenerator);
        }while(ai != population.at(randomIndex));

        TicTacToe::Token winner = game.match(*ai, *population.at(randomIndex));

        if(winner==TicTacToe::Token::X)
        {
            score += 1;
        }
        else if(winner==TicTacToe::Token::O)
        {
            score -= 1;
        }
    }

    return score;
}

void initRandom()
{
    //Random Number Generator
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    randomGenerator = default_random_engine(seed);
}

void initPopulation(vector<unique_ptr<NeuralNetAI>>& population)
{
    population.clear();

    std::ifstream file(SAVE_FILE_NAME, std::ios::binary);
    if(file.fail())
    {
        for(int i=0;i<POPULATION_SIZE; ++i)
        {
            unique_ptr<NeuralNetAI> individual(new NeuralNetAI(2,1,AMPLITUDE,2*AMPLITUDE));
            individual->mutate();
            population.push_back(move(individual));
        }
        return;
    }
    else
    {
        cereal::JSONInputArchive archive( file );

        for(int i=0;i<POPULATION_SIZE;++i)
            archive( *(population.at(i)) );
    }
}

void savePopulation(const vector<unique_ptr<NeuralNetAI>>& population)
{
    std::ofstream file(SAVE_FILE_NAME, std::ios::binary);
    if(!file.fail())
    {
        cereal::JSONOutputArchive archive( file );
        for(int i=0;i<POPULATION_SIZE;++i)
            archive( *(population.at(i)) );
    }
}

float calculateFitnessScores(vector<unique_ptr<NeuralNetAI>>& population, vector<float>& fitnessScores, float& minFitness, float& maxFitness)
{
    for(unsigned int i=0; i<population.size(); ++i)
    {
        float fitness = fitnessEval(population.at(i),population);
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
        float fitness = fitnessEval(population.at(i),population);
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

/*
bool verboseEndGame(TicTacToe::Token);

int main()
{
    /// Initialization
    const unsigned int NUMBER_OF_GAMES = 1000; //-1 to play an infinite number of games
    const string SAVE_FILE_X = "TicTacToeX.save";
    const string SAVE_FILE_O = "TicTacToeO.save";
    const bool VERBOSE_ENABLED = false;          //if(VERBOSE_ENABLED): the stats are calculated for playerO. Use with small NUMBER_OF_GAMES or with a human player

    TicTacToe game;

    CaseBasedAI playerX(9, 9, 1, 1);
    TicTacToeHuman playerO(9, 9, 1, 1);
    //CaseBasedAI playerO(9, 9, 1, 1);

    cout<<"start load"<<endl;

    GeneralAI::load<CaseBasedAI>(playerX, SAVE_FILE_X);
    //GeneralAI::load<NeuralNetAI>(playerO, SAVE_FILE_O);
    //GeneralAI::load<CaseBasedAI>(playerO, SAVE_FILE_O);

    cout<<"load completed"<<endl;
    cout<<"start games"<<endl;

    /// Play games
    for(unsigned int i=0; i != NUMBER_OF_GAMES; ++i)
    {
        TicTacToe::Token winner;
        winner = game.match(playerX, playerO);

        if(VERBOSE_ENABLED)
        {
            if (!verboseEndGame(winner))  //false if must stop for some reason
            {
                break;
            }
        }
    }

    cout<<"games completed"<<endl;
    cout<<"start save"<<endl;

    GeneralAI::save<CaseBasedAI>(playerX, SAVE_FILE_X);
    //GeneralAI::save<NeuralNetAI>(playerO, SAVE_FILE_O);
    //GeneralAI::save<CaseBasedAI>(playerO, SAVE_FILE_O);

    cout<<"save completed"<<endl;

    return 0;
}

bool verboseEndGame(TicTacToe::Token winner)
{
    ///Stats
    static vector<bool> recentGamesResults(100);
    static int gameNumber = 0;

    ///Evaluation
    switch(winner)
    {
        case TicTacToe::Token::None:
            cout<<"Tie game!"<<endl<<endl;
            break;

        case TicTacToe::Token::X:
            cout<<"Player X wins!"<<endl<<endl;
            recentGamesResults[gameNumber%100] = false;
            ++gameNumber;
            break;

        case TicTacToe::Token::O:
            cout<<"Player O wins!"<<endl<<endl;
            recentGamesResults[gameNumber%100] = true;
            ++gameNumber;
            break;
    }

    ///More stats stuff
    if(gameNumber>=100)  //Start checking stats
    {
        int totalWins=0;
        for(unsigned int i=0; i<recentGamesResults.size(); ++i)
        {
            if(recentGamesResults[i])
            {
                ++totalWins;
            }
        }

        float winPercentage = float(totalWins)/100.f;
        cout<<"Game #"<<gameNumber<<" winPercentage: "<<winPercentage<<endl;

        if(winPercentage >= .9f)
        {
            cout<<"It took "<<gameNumber<<" games to be so awesome!"<<endl;
            return false;
        }
    }

    return true;
}

*/
