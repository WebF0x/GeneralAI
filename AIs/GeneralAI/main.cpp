#include <iostream>
#include "GeneralAI.h"

using namespace std;

class DummyAI : public GeneralAI
{
    public:
        DummyAI(int a, int b, int c, int d) : GeneralAI(a,b,c,d) {}

        virtual vector<int> coreOutput(const vector<int>& input) const {cout<<"Outputting"<<endl; return vector<int>(OUTPUT_SIZE);}


    protected:
        virtual void coreLearn(const vector<int>& input, const vector<int>& output, float outcome) {cout<<"Learning"<<endl;}

        virtual vector<int> getMemory() const{return vector<int>();}
        virtual void setMemory(vector<int> memory) {}
};

int main()
{
    const unsigned int inputSize(10), outputSize(10);
    const int maxInput(3), maxOutput(100);
    const string fileName = "myDummySave";

    //Create GeneralAI
    GeneralAI *ai = new DummyAI(inputSize,outputSize,maxInput,maxOutput);

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
