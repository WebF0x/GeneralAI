#include <iostream>
#include "CaseBasedAI.h"

using namespace std;

int main()
{
    ///Init
    const unsigned int INPUT_SIZE(1), OUTPUT_SIZE(1);
    const int MAX_INPUT(1), MAX_OUTPUT(9);
    CaseBasedAI ai (INPUT_SIZE, OUTPUT_SIZE, MAX_INPUT, MAX_OUTPUT);
    const string FILE_NAME = "testSave";

    ///Load
    GeneralAI::load<CaseBasedAI>(ai, FILE_NAME);

    ///Test
    for(int i=0;i<10;++i)
    {
        vector<float> input(INPUT_SIZE,0);
        vector<float> output = ai.output(input);
        float out = output.at(0);
        int iOut = out;

        cout<<"Output:\n";
        cout<<iOut<<endl;
    }

    ///Load
    GeneralAI::save<CaseBasedAI>(ai, FILE_NAME);

    return 0;
}
