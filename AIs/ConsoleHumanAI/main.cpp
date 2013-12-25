#include <iostream>
#include "ConsoleHumanAI.h"

using namespace std;

int main()
{
    ConsoleHumanAI *ai = new ConsoleHumanAI();
    vector<int> question;
    question.push_back(3);
    question.push_back(2);
    question.push_back(1);

    ai->load("Fox.txt");

    vector<int> answer = ai->getOutput(question);

    ai->learn(question, answer, -1);

    ai->save("Fox.txt");

    return 0;
}
