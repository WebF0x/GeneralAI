#ifndef GENERALAI_H
#define GENERALAI_H

#include <stdexcept>
#include <tuple>

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
        virtual ~GeneralAI();

        ///Serialization (save/load)
        template<class AI, class Archive = cereal::BinaryOutputArchive>
        static void save(const AI& ai, const std::string& fileName)
        {
            std::ofstream os(fileName.data());
            Archive ar( os );
            ar( ai );
        }

        template<class AI, class Archive = cereal::BinaryInputArchive>
        static void load(AI& ai, const std::string& fileName)
        {
            std::ifstream is(fileName.data());
            Archive ar( is );
            ar( ai );
        }

        /// Returns AI's output
        std::vector<int> output(const std::vector<int>& input);

        /**
        *   Learn the outcome of output(input)
        *
        *   Worst outcome: -1.f
        *   Best outcome :  1.f
        **/
        void learn(const std::vector<int>& input, const std::vector<int>& output, float outcome);
        void learn(const std::tuple<std::vector<int>, std::vector<int>, float>& lesson);
        void learn(float outcome);  /// Learn the outcome of the lastDecision

        std::pair < std::vector<int>, std::vector<int> >       lastDecision() const;
        std::tuple< std::vector<int>, std::vector<int>, float> lastLesson() const;
        void reset();

        bool validInput(const std::vector<int>& input) const;
        bool validOutput(const std::vector<int>& output) const;
        bool validOutcome(float outcome) const;

    protected:
        static bool validVector(const std::vector<int>& v, unsigned int size, int amplitude);

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
        virtual void coreLearn(const std::vector<int>& input, const std::vector<int>& output, float outcome) = 0;
        virtual std::vector<int> coreOutput(const std::vector<int>& input) = 0;

        /// Short-term memory
        /*
        *   Should this be covered in GeneralAI or the worlds should take care of it?
        */
        std::pair<std::vector<int>,std::vector<int> > m_lastDecision;
        std::tuple<std::vector<int>, std::vector<int>, float> m_lastLesson;
        bool m_lastDecisionEnabled = false;
        bool m_lastLessonEnabled = false;
};

#endif // GENERALAI_H
