#include <iostream>
#include "HumanAI.h"

using namespace std;

int main()
{
    const unsigned int inputSize(10), outputSize(10);
    const int maxInput(3), maxOutput(100);
    const string fileName = "Fox.txt";

    //Create GeneralAI
    GeneralAI *ai = new ConsoleHumanAI(inputSize,outputSize,maxInput,maxOutput);

    //load
    try
    {
        ai->load(fileName);
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
    }

    //output
    try
    {
        vector<int> v(inputSize);
        vector<int> v2 = ai->output(v);

        cout<<"Output:\n";
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
        vector<int> input(inputSize), output(outputSize);
        float outcome = -1;
        ai->learn(input, output, outcome);
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
    }

    //save
    try
    {
        ai->save(fileName);
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
    }

    //Delete GeneralAI
    delete ai;

    return 0;
}
