#ifndef CASE_BASED_AI_HPP
#define CASE_BASED_AI_HPP

#include "StrongAI/AI/GeneralAI/GeneralAI.hpp"
#include <map>
#include <vector>
#include <chrono>
#include <random>
#include <limits>   //numeric_limits< int >::max()
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>

class CaseBasedAI : public GeneralAI
{
    friend cereal::access;

    public:
        CaseBasedAI( int inputSize, int outputSize, int maxInput, int maxOutput );
         virtual ~CaseBasedAI() {}

         const std::map< std::vector< double >, std::map< std::vector< double >, double > >& getMemory();
         unsigned int getMemorySize();

    private:
        virtual void coreLearn( const std::vector< double >& input, const std::vector< double >& output, double outcome );
        virtual std::vector< double > coreOutput( const std::vector< double >& input );

        //             Input                     Output       Outcome
        std::map< std::vector< double >, std::map< std::vector< double >, double > > m_memory;

        std::vector< double > randomOutput();
        std::vector< double > randomNewOutput( const std::map< std::vector< double >, double>& reactions );

        std::vector< double > bestOutput( const std::map< std::vector< double >, double>& reactions );

        template < class Archive >
        void serialize( Archive & ar )
        {
            ar( cereal::virtual_base_class< GeneralAI >( this ), m_memory );
        }
};

#endif // CASE_BASED_AI_HPP
