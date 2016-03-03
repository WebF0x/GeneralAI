#include <iostream>
#include "StrongAI/AI/RandomAI/RandomAI.hpp"

using namespace std;

int main()
{
    const unsigned int inputSize(10), outputSize(10);
    const int maxInput(3), maxOutput(100);
    const string fileName = "myDummySave.txt";

    RandomAI *ai = new RandomAI(inputSize,outputSize,maxInput,maxOutput);

    //output
    try
    {
        vector<float> v(inputSize);
        vector<float> v2 = ai->output(v);

        for(unsigned int i=0; i<outputSize; ++i)
        {
            cout<<v2[i]<<endl;
        }
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
    }

    //learn
    try
    {
        vector<float> input(inputSize), output(outputSize);
        float outcome = -1;
        ai->learn(input, output, outcome);
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
    }

    //Delete GeneralAI
    delete ai;

    return 0;
}
