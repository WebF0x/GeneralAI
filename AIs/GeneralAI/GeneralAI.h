#ifndef GENERALAI_H
#define GENERALAI_H

#include <stdexcept>
#include <tuple>
#include <random> //mt19937_64
#include <ctime>

//Serialization
#include <fstream>
#include <cereal/archives/JSON.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/xml.hpp>

/**
*   Abstract class for general artificial intelligence systems
*
*   Design pattern: Non-Virtual Interface
**/
class GeneralAI// : public SaveSystem
{
    friend cereal::access;

    public:
        const int INPUT_SIZE, OUTPUT_SIZE, INPUT_AMPLITUDE, OUTPUT_AMPLITUDE;

        GeneralAI(int inputSize, int outputSize, int inputAmplitude, int outputAmplitude);
        virtual ~GeneralAI(){}

        /// Returns AI's output
        std::vector<float> output(const std::vector<float>& input);

        /**
        *   Learn the outcome of output(input)
        *
        *   Worst outcome: -1.f
        *   Best outcome :  1.f
        **/
        void learn(const std::vector<float>& input, const std::vector<float>& output, float outcome);
        void learn(const std::tuple<std::vector<float>, std::vector<float>, float>& lesson);
        void learn(const std::pair<std::vector<float>,std::vector<float>>& decision, float outcome);
        void learn(float outcome);  /// Learn the outcome of the lastDecision

        std::pair < std::vector<float>, std::vector<float> >       lastDecision() const;
        std::tuple< std::vector<float>, std::vector<float>, float> lastLesson() const;
        void reset();

        bool validInput(const std::vector<float>& input) const;
        bool validOutput(const std::vector<float>& output) const;
        bool validOutcome(float outcome) const;

        static float randomProbability();

        ///Serialization (save/load)
        template<class AI, class Archive = cereal::BinaryOutputArchive>
        static bool save(const AI& ai, const std::string& fileName)
        {
            std::ofstream file(fileName, std::ios::binary);
            if(file.fail()) return false;

            Archive archive( file );
            archive( ai );

            return true;
        }

        template<class AI, class Archive = cereal::BinaryInputArchive>
        static bool load(AI& ai, const std::string& fileName)
        {
            std::ifstream file(fileName, std::ios::binary);
            if(file.fail()) return false;

            Archive archive( file );
            archive( ai );

            return true;
        }

        static std::mt19937_64 m_randomNumberGenerator; //Shared random number generator
        static bool validVector(const std::vector<float>& v, unsigned int size, int amplitude);

    private:
        //Serialization
        /*
        *   Copy/paste this method in subclasses
        *
        *   Use this format:
        *       ar(cereal::virtual_base_class<Base>( this ), member1, member2, ...);
        *
        *   Is there a neater way to do this?
        *   Make this method use a virtual method maybe...
        *   Apparently, templates functions can't be virtual...
        */
        template <class Archive>
        void serialize( Archive & ar )
        {
            //ar(cereal::virtual_base_class<Base>( this ), member1, member2, ...);

            ar(const_cast<int &>(INPUT_SIZE),
               const_cast<int &>(OUTPUT_SIZE),
               const_cast<int &>(INPUT_AMPLITUDE),
               const_cast<int &>(OUTPUT_AMPLITUDE));
        }

        /// Subclasses must implement these methods
        virtual void coreLearn(const std::vector<float>& input, const std::vector<float>& output, float outcome) = 0;
        virtual std::vector<float> coreOutput(const std::vector<float>& input) = 0;

        /// Short-term memory
        /*
        *   Should this be covered in GeneralAI or the worlds should take care of it?
        *   This is useless overhead for some AI's
        */
        std::pair<std::vector<float>,std::vector<float> > m_lastDecision;
        std::tuple<std::vector<float>, std::vector<float>, float> m_lastLesson;
        bool m_lastDecisionEnabled = false;
        bool m_lastLessonEnabled = false;
};

#endif // GENERALAI_H
