#ifndef SITUATION_H
#define SITUATION_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Situation /**/: std::vector<int>
{
    public:
        Situation(const Situation&);
        //Situation(const string& data);

        Situation(const std::vector<int>&);

        bool operator==(const Situation&) const;
        Situation operator=(const Situation&);

        int size() const;

        std::string toString() const;
        static Situation fromString(const string&);


    private:
        std::vector<int> m_variables;
};

#endif // SITUATION_H
