#ifndef HUMAN_H
#define HUMAN_H

#include "IntelligentAgent.h"
#include <iostream>

class Human : public IntelligentAgent
{
    public:
        Human();
        virtual ~Human();

        virtual void run();

    protected:
        void load(std::vector<int> data);
        std::vector<int> getData();

    private:
};

#endif // HUMAN_H
