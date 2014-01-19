#ifndef GENERALWORLD_H
#define GENERALWORLD_H

#include "../../AIs/GeneralAI/GeneralAI.h"
#include <vector>
#include <stdexcept>

class GeneralWorld
{
    public:
        GeneralWorld(unsigned int actorCount);
        virtual ~GeneralWorld();

        void run(const std::vector<GeneralAI*>& actors);

        const unsigned int ACTOR_COUNT;

    private:
        virtual void coreRun(const std::vector<GeneralAI*>& actors) = 0;

};

#endif // GENERALWORLD_H
