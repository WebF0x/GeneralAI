#include <iostream>
#include "CaseBasedAI.h"

using namespace std;

int main()
{
    GeneralAI *ai = new CaseBasedAI(2,2,2,2);

    vector<int> v(2);

    v = ai->output(v);

    cout<<v[0];

    delete ai;

    return 0;
}
