#include <iostream>
#include <map>
#include <ctime>
#include "StrongAI/AI/DarwinAI/DarwinAI.hpp"
#include <cereal/types/memory.hpp>

using namespace std;

const int AMPLITUDE = 100;

void manualTesting(unique_ptr<NeuralNetAI>& individual)
{
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

class AdderDarwinAI : public DarwinAI
{
    public:
    AdderDarwinAI() : DarwinAI(2,1,AMPLITUDE,2*AMPLITUDE)
    {

    }

    private:
    //Task: Output the sum of the two inputs
    virtual float fitnessEval(NeuralNetAI& ai)
    {
        float fitness = 0;  //Perfect fitness is 0 (in this case)

        for(int i=0; i<10; ++i)
        {
            float a = GeneralAI::randomProbability()*100;
            float b = GeneralAI::randomProbability()*100;
            float sum = a+b;

            vector<float> input({a,b});

            auto output = ai.output(input);
            float out = output[0];

            fitness -= abs(out-sum);
        }

        return fitness;
    }
};

int main()
{
    cout<<"Generating initial population"<<endl;
    AdderDarwinAI population;

    cout<<"Population is evolving"<<endl;
    for(int i=0; i<100; i++)
    {
        cout<<"\t"<<i<<" %"<<endl;
        population.evolve(100);
    }

    cout<<"Saving population"<<endl;
    //GeneralAI::save<AdderDarwinAI>, cereal::JSONOutputArchive>(AdderDarwinAI, "save.txt");

    cout<<"Selecting best individual"<<endl;
    unique_ptr<NeuralNetAI>& champion = population.bestIndividual();

    cout<<"Manual Testing"<<endl;
    manualTesting(champion);

    return 0;
}
