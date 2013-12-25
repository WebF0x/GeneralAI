#include "ConsoleHumanAI.h"

using namespace std;

vector<int> ConsoleHumanAI::getOutput(const vector<int>& input) const
{
    cout<<"What is your Output?"<<endl
        <<"===================="<<endl;

    //Display inputs
    cout<<"\tInput"<<endl
        <<"\t-----"<<endl;

    for(unsigned int i=0; i<input.size(); ++i)
    {
        cout<<"\t\t"<<input[i]<<endl;
    }

    //Ask outputs
    cout<<"\tOutput"<<endl
        <<"\t------"<<endl;

    int outputSize;
    cout<<"\t\tOutput size: ";
    cin>>outputSize;

    vector<int> output;
    for(int i=0; i<outputSize; ++i)
    {
        cout<<"\t\tOutput "<<i<<": ";

        int userInput;
        cin>>userInput;
        output.push_back(userInput);
    }

    return output;
}

void ConsoleHumanAI::learn(const std::vector<int>& input, const std::vector<int>& output, float outcome)
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

    int memorySize;
    cout<<"\tMemory size: ";
    cin>>memorySize;

    vector<int> memory;
    for(int i=0; i<memorySize; ++i)
    {
        cout<<"\tMemory "<<i<<": ";

        int userInput;
        cin>>userInput;
        memory.push_back(userInput);
    }

    return memory;
}

bool ConsoleHumanAI::setMemory(std::vector<int> memory)
{
    cout<<"From now on, this is your memory!"<<endl
        <<"================================="<<endl
        <<endl
        <<"\tMemory: ";

    printVector(memory);

    cout<<endl
        <<endl
        <<endl;

    return true;
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

    cout<<']';
}
