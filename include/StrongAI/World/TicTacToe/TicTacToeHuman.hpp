#ifndef TIC_TAC_TOE_HUMAN_HPP
#define TIC_TAC_TOE_HUMAN_HPP

#include "StrongAI/AI/HumanAI/HumanAI.hpp"

#include <iostream>
#include <vector>

class TicTacToeHuman : public HumanAI
{
    public:
        TicTacToeHuman( int inputSize, int outputSize, int maxInput, int maxOutput );

    private:
        std::vector< float > coreOutput( const std::vector< float >& input );
        void coreLearn( const std::vector< float >& input, const std::vector< float >& output, float outcome ) {}

        void visualizeInput( const std::vector< float >& input );
        char inputToChar( float input );
};

#endif // TIC_TAC_TOE_HUMAN_HPP
