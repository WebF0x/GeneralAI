#include <iostream>
#include "GeneralAI.h"

using namespace std;

class DummyAI : public GeneralAI
{
    public:
        DummyAI(int a, int b, int c, int d) : GeneralAI(a,b,c,d) {}

        virtual vector<int> coreOutput(const vector<int>& input) const {return vector<int>(1);}


    protected:
        virtual void coreLearn(const vector<int>& input, const vector<int>& output, float outcome) {}
        //virtual vector<int> coreOutput(const vector<int>& input) const {return vector<int>();}

        virtual vector<int> getMemory() const{return vector<int>();}
        virtual void setMemory(vector<int> memory) {}
};

int main()
{
    const unsigned int inputSize(1), outputSize(1);
    const int maxInput(1), maxOutput(1);
    const string fileName = "myDummySave";

    //Create DummyAI
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
        vector<int> v(1);
        ai->output(v);
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
    }

    //learn
    try
    {
        vector<int> input(1), output(1);
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

    //Delete DummyAI
    delete ai;

    return 0;
}
