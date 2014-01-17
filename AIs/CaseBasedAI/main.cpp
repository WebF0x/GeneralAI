#include <iostream>
#include "CaseBasedAI.h"

using namespace std;

int main()
{
    const unsigned int INPUT_SIZE = 2;
    const unsigned int OUTPUT_SIZE = 2;

    vector<int> input(INPUT_SIZE);
    vector<int> output(OUTPUT_SIZE);
        output[0] = 2;
    float outcome = .90f;





    GeneralAI *ai = new CaseBasedAI(INPUT_SIZE,OUTPUT_SIZE,2,2);

    ai->learn(input,output,outcome);

    vector<int> answer = ai->output(input);

    cout<<answer[0];

    delete ai;

    return 0;
}
