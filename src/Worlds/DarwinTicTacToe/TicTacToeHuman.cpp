#include "TicTacToeHuman.h"

using namespace std;

TicTacToeHuman::TicTacToeHuman(int inputSize, int outputSize, int maxInput, int maxOutput)
    : HumanAI(inputSize, outputSize, maxInput, maxOutput)
{

}

void TicTacToeHuman::visualizeInput(const std::vector<float>& input)
{

    cout<<inputToChar(input[6])<<"_|_"<<inputToChar(input[7])<<"_|_"<<inputToChar(input[8])<<endl;
    cout<<inputToChar(input[3])<<"_|_"<<inputToChar(input[4])<<"_|_"<<inputToChar(input[5])<<endl;
    cout<<inputToChar(input[0])<<" | "<<inputToChar(input[1])<<" | "<<inputToChar(input[2])<<endl;
}

vector<float> TicTacToeHuman::coreOutput(const vector<float>& input)
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

    vector<float> output(9,0);
    output.at(userInput-1) = 1;
    return output;
}

char TicTacToeHuman::inputToChar(float input)
{
    if(input <= -.5f) return 'X';
    if(input >=  .5f) return 'O';
    else return ' ';
}
