#include <iostream>
#include "GeneralAI.h"

using namespace std;

class Test : public GeneralAI
{
    public:
        Test(int a, int b, int c, int d) : GeneralAI(a,b,c,d) {}

    protected:
        virtual void coreLearn(const vector<int>& input, const vector<int>& output, float outcome) {}
        virtual vector<int> coreOutput(const vector<int>& input) const {return vector<int>();};

        virtual vector<int> getMemory() const{return vector<int>();};
        virtual bool setMemory(vector<int> memory) {return true;};
};

int main()
{
    Test *t;

    try
    {
        t = new Test(1,1,1,-1);
    }
    catch (const std::exception& e)
    {
        cout << "Constructor exception: " << e.what() << endl;
        return 1;
    }

    try
    {
        t->learn(std::vector<int>(1), std::vector<int>(1), 1.f);
    }
    catch (const std::exception& e)
    {
        cout << "Learn exception: " << e.what() << endl;
        delete t;
        return 1;
    }

    delete t;

    return 0;
}
