#ifndef TIC_TAC_TOE_HUMAN_HPP
#define TIC_TAC_TOE_HUMAN_HPP

#include "StrongAI/AI/HumanAI/HumanAI.hpp"
#include "StrongAI/World/DarwinTicTacToe/TicTacToe.hpp"

#include <iostream>
#include <vector>

class TicTacToeHuman : public HumanAI
{
    public:
        TicTacToeHuman( int inputSize, int outputSize, int maxInput, int maxOutput );

    private:
        std::vector< double > coreOutput( const std::vector< double >& input );
        void coreLearn( const std::vector< double >& input, const std::vector< double >& output, double outcome ) {}

        void visualizeInput( const std::vector< double >& input );
        char inputToChar( double input );
};

#endif // TIC_TAC_TOE_HUMAN_HPP
