#include <iostream>
#include "HumanAI.h"

using namespace std;

int main()
{
    const unsigned int inputSize(10), outputSize(10);
    const int maxInput(3), maxOutput(100);
    const string fileName = "Fox.txt";

    HumanAI ai(inputSize,outputSize,maxInput,maxOutput);

    GeneralAI::load<HumanAI, cereal::JSONInputArchive>(ai, fileName);
    GeneralAI::save<HumanAI, cereal::JSONOutputArchive>(ai, fileName);

    return 0;
}
