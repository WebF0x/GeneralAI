#ifndef EXAMPLEAI_H
#define EXAMPLEAI_H

#include "../GeneralAI.h"

class ExampleAI : public GeneralAI
{
    public:
        ExampleAI(int inputSize, int outputSize, int maxInput, int maxOutput);

    private:
        std::vector<int> coreOutput(const std::vector<int>& input);
        void coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome);

        template <class Archive>
        void serialize( Archive & ar )
        {
            ar( cereal::virtual_base_class<GeneralAI>(this) );

            /**
                You can serialize any variables that you want like this:
                    ar( cereal::virtual_base_class<GeneralAI>(this), var1, var2, varN );
            **/
        }

    friend cereal::access;
};

#endif // EXAMPLEAI_H
