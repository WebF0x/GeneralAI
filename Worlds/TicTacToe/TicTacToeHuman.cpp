#include "TicTacToeHuman.h"

using namespace std;

TicTacToeHuman::TicTacToeHuman(int inputSize, int outputSize, int maxInput, int maxOutput)
    : HumanAI(inputSize, outputSize, maxInput, maxOutput)
{

}

void TicTacToeHuman::visualizeInput(const std::vector<int>& input)
{
    cout<<inputToChar(input[6])<<"_|_"<<inputToChar(input[7])<<"_|_"<<inputToChar(input[8])<<endl;
    cout<<inputToChar(input[3])<<"_|_"<<inputToChar(input[4])<<"_|_"<<inputToChar(input[5])<<endl;
    cout<<inputToChar(input[0])<<" | "<<inputToChar(input[1])<<" | "<<inputToChar(input[2])<<endl;
}

char TicTacToeHuman::inputToChar(int input)
{
    switch (input)
    {
        case 1: return 'X';
        case -1: return 'O';
        default: return ' ';
    }
}

vector<int> TicTacToeHuman::coreOutput(const vector<int>& input)
{
    cout<<"TicTacToe Board:"<<endl
        <<"================"<<endl;

    visualizeInput(input);
    cout<<endl;

    cout<<"What is your move? (Use NumPad)"<<endl
        <<"==============================="<<endl;

    int userInput;
    do
    {
        cout<<"";
        cin>>userInput;
    }while(userInput < 1 || userInput > 9);
    cout<<endl;

    return vector<int>(1, userInput-5); //Must be in range [-4,4]
}

void TicTacToeHuman::coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome)
{

}

vector<int> TicTacToeHuman::getMemory() const
{
    return vector<int>();
}

void TicTacToeHuman::setMemory(std::vector<int> memory)
{

}
