#include "HumanAI.h"

using namespace std;

ConsoleHumanAI::ConsoleHumanAI(unsigned int inputSize, unsigned int outputSize, int maxInput, int maxOutput)
    : GeneralAI(inputSize, outputSize, maxInput, maxOutput)
{

}

vector<int> ConsoleHumanAI::coreOutput(const vector<int>& input) const
{
    cout<<"What is your Output?"<<endl
        <<"===================="<<endl;

    //Display inputs
    cout<<"\tInput"<<endl
        <<"\t-----"<<endl
        <<"\t";
    printVector(input);
    cout<<endl;

    //Ask outputs
    cout<<"\tOutput"<<endl
        <<"\t------"<<endl
        <<"\t\t( Between "<<-OUTPUT_AMPLITUDE<<" and "<<OUTPUT_AMPLITUDE<<" )"<<endl;

    vector<int> output;
    for(int i=0; i<OUTPUT_SIZE; ++i)
    {
        cout<<"\t\tOutput "<<i<<"/"<<OUTPUT_SIZE-1<<": "<<endl;

        int userInput;

        do
        {
            cout<<"\t\t";
            cin>>userInput;
        }while(userInput < -OUTPUT_AMPLITUDE || userInput > OUTPUT_AMPLITUDE);
        cout<<endl;

        output.push_back(userInput);
    }

    return output;
}

void ConsoleHumanAI::coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome)
{
    cout<<"Learn this"<<endl
        <<"=========="<<endl;

    cout<<"\tInput: ";
    printVector(input);
    cout<<endl
        <<endl;

    cout<<"\tOutput: ";
    printVector(output);
    cout<<endl
        <<endl;

    cout<<"\tOutcome: "<<outcome<<endl
        <<endl;
}

vector<int> ConsoleHumanAI::getMemory() const
{
    //Ask outputs
    cout<<"Write your memory"<<endl
        <<"================="<<endl;

    unsigned int memorySize;
    cout<<"\tMemory size: ";
    cin>>memorySize;

    vector<int> memory(memorySize);
    for(unsigned int i=0; i<memorySize; ++i)
    {
        cout<<"\tMemory "<<i<<": ";

        int userInput;
        cin>>userInput;
        memory[i] = userInput;
    }

    return memory;
}

void ConsoleHumanAI::setMemory(std::vector<int> memory)
{
    cout<<"From now on, this is your memory!"<<endl
        <<"================================="<<endl
        <<endl
        <<"\tMemory: ";

    printVector(memory);

    cout<<endl
        <<endl
        <<endl;

}

void ConsoleHumanAI::printVector(const std::vector<int>& vect) const
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
