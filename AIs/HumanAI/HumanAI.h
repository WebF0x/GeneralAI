#ifndef HUMANAI_H
#define HUMANAI_H

#include "../GeneralAI/GeneralAI.h"
#include <iostream>
#include <string>

#include <cereal/types/string.hpp>

class HumanAI : public GeneralAI
{
    friend cereal::access;

    public:
        HumanAI(int inputSize, int outputSize, int maxInput, int maxOutput);

    private:
        virtual std::vector<float> coreOutput(const std::vector<float>& input) ;
        virtual void coreLearn(const std::vector<float>& input, const std::vector<float>& output, float outcome);
        virtual void visualizeInput(const std::vector<float>& input);

        void printVector(const std::vector<float>& vect) const;

        template <class Archive>
        void save( Archive & ar ) const
        {
            std::cout<<"Write notes to save:"<<std::endl;

            std::string memory;
            std::getline (std::cin,memory);

            std::cout<<std::endl;

            ar(cereal::virtual_base_class<GeneralAI>( this ), memory);
        }

        template <class Archive>
        void load( Archive & ar )
        {
            std::string memory;
            ar(cereal::virtual_base_class<GeneralAI>( this ), memory);

            std::cout<<"Here is your memory:"<<std::endl<<memory<<std::endl;
        }

};

//Separate the serialization in two parts: save and load
namespace cereal
{
  template <class Archive>
  struct specialize<Archive, HumanAI, cereal::specialization::member_load_save> {};
}

#endif // HUMANAI_H
