#include <iostream>
#include "ExampleAI.h"

using namespace std;

int main()
{
    const int INPUT_SIZE(2), OUTPUT_SIZE(2);
    const int INPUT_AMPLITUDE(2), OUTPUT_AMPLITUDE(2);
    const string FILE_NAME = "example.save";

    ExampleAI ai = ExampleAI(INPUT_SIZE,OUTPUT_SIZE,INPUT_AMPLITUDE,OUTPUT_AMPLITUDE);

    vector<float> input(INPUT_SIZE);

    cout<<"Input:"<<endl;
    for(auto val : input)
    {
        cout<<'\t'<<val<<endl;
    }

    ///Test output
    vector<float> output = ai.output(input);

    cout<<"Output:"<<endl;
    for(auto value : output)
    {
        cout<<'\t'<<value<<endl;
    }

    ///Test learn
    float outcome = -1;
    ai.learn(input, output, outcome);

    ///Test save/load
    GeneralAI::save<ExampleAI>(ai, FILE_NAME);

    ExampleAI clone(0,0,0,0);
    GeneralAI::load<ExampleAI>(clone, FILE_NAME);

    if(clone.INPUT_SIZE == INPUT_SIZE &&
       clone.OUTPUT_SIZE == OUTPUT_SIZE &&
       clone.INPUT_AMPLITUDE == INPUT_AMPLITUDE &&
       clone.OUTPUT_AMPLITUDE == OUTPUT_AMPLITUDE)
    {
        cout<<"Save and load successful!"<<endl;
    }

    ///Test JSON save format
    const string JSON_FILE_NAME = "example.JSON";
    GeneralAI::save<ExampleAI, cereal::JSONOutputArchive>(clone, JSON_FILE_NAME);
    cout<<endl
        <<"Open the file "<<JSON_FILE_NAME<<"!"<<endl
        <<"JSON is a human readable format really useful for debugging!"<<endl
        <<"You can also use XML"<<endl
        <<"You can also use the default format (binary) when you are done debugging, it is way more efficient"<<endl;


    return 0;
}
