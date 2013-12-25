#ifndef DECISION_H
#define DECISION_H

#include <iostream>
#include "Situation.h"
#include <string>
#include <sstream>

enum Result
{
    Good,
    Neutral,
    Bad
};

class Decision
{
    public:
        Decision(const Situation&, const int reaction, const Result&);
        //Decision(const string& data);

        Situation getSituation() const;
        void setSituation(const Situation&);

        int getReaction() const;
        void setReaction(const int);

        Result getResult() const;
        void setResult(const Result&);

        Decision operator=(const Decision&);
        bool operator==(const Decision&) const;

        std::string toString() const;

        static Decision decisionFromString(std::string);
        static Result resultFromString(const std::string&);

    private:
        Situation m_situation;
        int m_reaction;
        Result m_result;
};

#endif // DECISION_H
