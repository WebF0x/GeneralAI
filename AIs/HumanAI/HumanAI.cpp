#include "HumanAI.h"

using namespace std;

HumanAI::HumanAI(int inputSize, int outputSize, int maxInput, int maxOutput)
    : GeneralAI(inputSize, outputSize, maxInput, maxOutput)
{

}

vector<int> HumanAI::coreOutput(const vector<int>& input)
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

    vector<int> output;
    for(int i=0; i<OUTPUT_SIZE; ++i)
    {
        cout<<"Output "<<i<<"/"<<OUTPUT_SIZE-1<<": "<<endl;

        int userInput;

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

void HumanAI::coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome)
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

vector<int> HumanAI::getMemory() const
{
    //Ask outputs
    cout<<"Write your memory"<<endl
        <<"================="<<endl;

    unsigned int memorySize;
    cout<<"Memory size: ";
    cin>>memorySize;

    vector<int> memory(memorySize);
    for(unsigned int i=0; i<memorySize; ++i)
    {
        cout<<"Memory "<<i<<": ";

        int userInput;
        cin>>userInput;
        memory[i] = userInput;
    }

    return memory;
}

void HumanAI::setMemory(std::vector<int> memory)
{
    cout<<"From now on, this is your memory!"<<endl
        <<"================================="<<endl
        <<endl
        <<"Memory: ";

    printVector(memory);

    cout<<endl
        <<endl
        <<endl;

}

void HumanAI::printVector(const std::vector<int>& vect) const
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

void HumanAI::visualizeInput(const vector<int>& input)
{
    printVector(input);
}
