#include "StrongAI/AI/HumanAI/HumanAI.hpp"

using namespace std;

HumanAI::HumanAI(int inputSize, int outputSize, int maxInput, int maxOutput)
    : GeneralAI(inputSize, outputSize, maxInput, maxOutput)
{

}

vector<float> HumanAI::coreOutput(const vector<float>& input)
{
    cout<<"What is your Output?"<<endl
        <<"===================="<<endl;

    //Display inputs
    cout<<"Input"<<endl
        <<"-----"<<endl;

    visualizeInput(input);
    cout<<endl;

    //Ask outputs
    cout<<"Output"<<endl
        <<"------"<<endl
        <<"( Between "<<-OUTPUT_AMPLITUDE<<" and "<<OUTPUT_AMPLITUDE<<" )"<<endl;

    vector<float> output;
    for(int i=0; i<OUTPUT_SIZE; ++i)
    {
        cout<<"Output "<<i<<"/"<<OUTPUT_SIZE-1<<": "<<endl;

        float userInput;

        do
        {
            cout<<"";
            cin>>userInput;
        }while(userInput < -OUTPUT_AMPLITUDE || userInput > OUTPUT_AMPLITUDE);
        cout<<endl;

        output.push_back(userInput);
    }

    return output;
}

void HumanAI::coreLearn(const std::vector<float>& input, const std::vector<float>& output, float outcome)
{
    cout<<"Learn this"<<endl
        <<"=========="<<endl;

    cout<<"Input: ";
    visualizeInput(input);
    cout<<endl
        <<endl;

    cout<<"Output: ";
    printVector(output);
    cout<<endl
        <<endl;

    cout<<"Outcome: "<<outcome<<endl
        <<endl;
}

void HumanAI::printVector(const std::vector<float>& vect) const
{
    cout<<'[';

    if(!vect.empty())
    {
        cout<<vect[0];
        for(unsigned int i=1; i<vect.size(); ++i)
        {
            cout<<", "<<vect[i];
        }
    }

    cout<<']'<<endl;
}

void HumanAI::visualizeInput(const vector<float>& input)
{
    printVector(input);
}
