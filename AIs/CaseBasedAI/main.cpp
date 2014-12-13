#include <iostream>
#include "CaseBasedAI.h"

using namespace std;

int main()
{
    ///Init
    const unsigned int INPUT_SIZE(1), OUTPUT_SIZE(2);
    const int MAX_INPUT(1), MAX_OUTPUT(1);
    CaseBasedAI ai (INPUT_SIZE, OUTPUT_SIZE, MAX_INPUT, MAX_OUTPUT);
    const string FILE_NAME = "testSave";

    ///Load
    GeneralAI::load<CaseBasedAI>(ai, FILE_NAME);


    ///Test
    for(int i=0;i<1000;++i)
    {
        vector<float> input(INPUT_SIZE,0);
        vector<float> aiOutput = ai.output(input);

        ai.learn(-1.f);

        cout<<"Output:\n";
        for(unsigned int i=0; i<OUTPUT_SIZE; ++i)
        {
            cout<<aiOutput[i]<<endl;
        }
    }

    ///Load
    GeneralAI::save<CaseBasedAI>(ai, FILE_NAME);

    return 0;
}
