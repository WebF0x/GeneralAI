#include "GeneralWorld.h"

using namespace std;

GeneralWorld::GeneralWorld(unsigned int actorCount) : ACTOR_COUNT(actorCount)
{
}

GeneralWorld::~GeneralWorld()
{
}

void GeneralWorld::run(const std::vector<GeneralAI*>& actors)
{
    if(actors.size() != ACTOR_COUNT)
    {
        throw length_error(string( "invalid actors vector size" ));
    }

    coreRun(actors);
}
