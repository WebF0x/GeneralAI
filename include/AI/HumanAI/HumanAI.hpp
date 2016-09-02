#pragma once

#include "AI/GeneralAI/GeneralAI.hpp"
#include <iostream>

class HumanAI : public GeneralAI
{
    friend cereal::access;

    public:
        HumanAI( int inputSize, int outputSize, int maxInput, int maxOutput );
        virtual ~HumanAI() {}

    private:
        virtual std::vector< double > coreOutput( const std::vector< double >& input ) ;
        virtual void coreLearn( const std::vector< double >& input, const std::vector< double >& output, double outcome );
        virtual void visualizeInput( const std::vector< double >& input );

        void printVector( const std::vector< double >& vect ) const;

        template < class Archive >
        void save( Archive & ar ) const
        {
            std::cout << "Write memory to save:" << std::endl;

            std::string memory;
            std::cin>>memory;

            std::cout << std::endl;

            ar( cereal::virtual_base_class< GeneralAI >( this ), memory );
        }

        template < class Archive >
        void load( Archive & ar )
        {
            std::string memory;
            ar( cereal::virtual_base_class< GeneralAI >( this ), memory );

            std::cout << "Here is your memory:" << std::endl
                      << memory << std::endl;
        }
};

//Separate the serialization in two parts: save and load
namespace cereal
{
  template < class Archive >
  struct specialize< Archive, HumanAI, cereal::specialization::member_load_save > {};
}
