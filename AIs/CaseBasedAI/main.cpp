#include <iostream>
#include "CaseBasedAI.h"

using namespace std;

int main()
{
    /// Initialization
    const unsigned int INPUT_SIZE(1), OUTPUT_SIZE(2);
    const int MAX_INPUT(1), MAX_OUTPUT(1);

    CaseBasedAI ai (INPUT_SIZE, OUTPUT_SIZE, MAX_INPUT, MAX_OUTPUT);

    //Testing if randomNewOutput works normally
    for(int i=0;i<10;++i)
    {
        vector<int> input(INPUT_SIZE);
        vector<int> aiOutput = ai.output(input);

        ai.learn(-1.f);

        cout<<"Output:\n";
        for(unsigned int i=0; i<OUTPUT_SIZE; ++i)
        {
            cout<<aiOutput[i]<<endl;
        }
    }

    return 0;
}
