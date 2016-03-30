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

         const std::map< std::vector< float >, std::map< std::vector< float >, float > >& getMemory();
         unsigned int getMemorySize();

    private:
        virtual void coreLearn( const std::vector< float >& input, const std::vector< float >& output, float outcome );
        virtual std::vector< float > coreOutput( const std::vector< float >& input );

        //             Input                     Output       Outcome
        std::map< std::vector< float >, std::map< std::vector< float >, float > > m_memory;

        float randomProbability();
        std::vector< float > randomOutput();
        std::vector< float > randomNewOutput( const std::map< std::vector< float >, float>& reactions );

        std::vector< float > bestOutput( const std::map< std::vector< float >, float>& reactions );

        template < class Archive >
        void serialize( Archive & ar )
        {
            ar( cereal::virtual_base_class< GeneralAI >( this ), m_memory );
        }
};

#endif // CASE_BASED_AI_HPP
