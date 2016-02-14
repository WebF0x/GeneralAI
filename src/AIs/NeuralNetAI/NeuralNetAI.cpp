#include "NeuralNetAI.h"

using namespace std;

NeuralNetAI::NeuralNetAI(int inputSize, int outputSize, int maxInput, int maxOutput)
    : GeneralAI(inputSize, outputSize, maxInput, maxOutput),
    NUMBER_OF_NODES(2+INPUT_SIZE+OUTPUT_SIZE+INIT_NUMBER_OF_NEURONS),
    MAX_WEIGHT_VALUE(sqrt(numeric_limits<float>::max()/NUMBER_OF_NODES)),
    MAX_NODE_VALUE(MAX_WEIGHT_VALUE)
{
    m_nodes = vector<Node>(NUMBER_OF_NODES, Node());
    resetNodesValues();
}

void NeuralNetAI::coreLearn(const vector<float>& input, const vector<float>& output, float outcome)
{
    if(outcome==0.f) return;    //Can't learn neutral lessons, only good or bad

    for(int c=0; c<MAX_NUMBER_OF_LEARN_CYCLES; ++c)
    {
        //Check if AI's output matches given output
        vector<float> out = this->output(input);

        bool kindaClose = true;
        for(unsigned int i=0; i<out.size(); ++i)
        {
            if(abs(out[i]-output[i]) > abs(output[i]) * ACCEPTABLE_ERROR )
            {
                kindaClose = false;
                break;
            }
        }

        //If close to something good or far from something bad, stop
        if(kindaClose == (outcome>0)) return;
        else mutate();
    }
}

vector<float> NeuralNetAI::coreOutput(const vector<float>& input)
{
    resetNodesValues();

    //Init input nodes
    setInput(input);

    //Compute until triggered or until we bust MAX_NUMBER_OF_CYCLES
    for(int i=0; i<MAX_NUMBER_OF_CYCLES && !triggered(); ++i)
    {
        computeCycle();
    }

    //Return output nodes
    vector<float> output;
    auto start = m_nodes.begin()+2+INPUT_SIZE;
    auto stop = start + OUTPUT_SIZE;
    for(auto it=start; it!=stop; ++it)
    {
        output.push_back(function(it->value));
    }

    return output;
}

void NeuralNetAI::computeCycle()
{
    vector<float> newValues;

    //Calculate new node values
    for(auto& node : m_nodes)
    {
        float newValue = 0;
        for(auto& synapse : node.incomingSynapses)
        {
            const int SOURCE = synapse.first;
            const float WEIGHT = synapse.second;
            newValue += m_nodes.at(SOURCE).value * WEIGHT;
        }

        /** newValue is sometimes not a number (NaN),  */
        /*
        if(isnan(newValue))
        {
            cout<<"NANNNN"<<node.value<<endl;
            int a;
            cin>>a;
        }
        //*/

        newValues.push_back(newValue);
    }

    //Update node values
    for(int i=0; i<NUMBER_OF_NODES; ++i)
    {
        setNodeValue(i, newValues.at(i));
    }
}

/**
*   Randomly create, destroy and mutate a few synapses
**/
void NeuralNetAI::mutate()
{
    for(int DEST=0; DEST<NUMBER_OF_NODES; ++DEST)
    {
        if(DEST==1) continue;   //Skip bias node
        if(2 <= DEST && DEST < 2+INPUT_SIZE) continue;   //Skip input nodes

        for(int SOURCE=0; SOURCE<NUMBER_OF_NODES; ++SOURCE)
        {
            if(SOURCE==0) continue; //Skip trigger node
            if(2+INPUT_SIZE <= SOURCE && SOURCE < NUMBER_OF_NODES-INIT_NUMBER_OF_NEURONS) continue;   //Skip output nodes

            //Now we're targetting a valid synapse (SOURCE to DEST).
            //There's a small probability the synapse gets killed
            if(randomProbability() < CHANCE_TO_MUTATE_KILL)
            {
                //Kill synapse (if it exists)
                auto& synapses = m_nodes.at(DEST).incomingSynapses;
                if(synapses.find(SOURCE) != synapses.end())
                {
                    m_nodes.at(DEST).incomingSynapses.erase(SOURCE);
                }
            }
            else
            {
                //Find existing synapse or create it
                map<int, float>& synapses = m_nodes.at(DEST).incomingSynapses;
                map<int, float>::iterator synapse = synapses.insert(synapses.begin(), make_pair(SOURCE, INIT_WEIGHT_VALUE));

                //Small probability to mutate synapse
                const int SYNAPSE_INDEX = synapse->first;
                float mutatedWeight = synapse->second;

                if(randomProbability() < CHANCE_TO_MUTATE_ADD)
                {
                    uniform_real_distribution<float> dist(-AMPLITUDE_ADD, AMPLITUDE_ADD);
                    mutatedWeight += dist(m_randomNumberGenerator);
                }

                if(randomProbability() < CHANCE_TO_MUTATE_MUL)
                {
                    uniform_real_distribution<float> dist(-AMPLITUDE_MUL, AMPLITUDE_MUL);
                    mutatedWeight *= dist(m_randomNumberGenerator);
                }

                setSynapseWeight(DEST, SYNAPSE_INDEX, mutatedWeight);
            }
        }
    }
}

void NeuralNetAI::setSynapseWeight(int nodeIndex, int synapseSourceIndex, float weight)
{
    //Check if node is valid
    if(nodeIndex >= NUMBER_OF_NODES) return;
    Node& node = m_nodes.at(nodeIndex);

    //Check if synapse exists
    auto& synapses = node.incomingSynapses;
    if(synapses.find(synapseSourceIndex) == synapses.end()) return;

    //Force weight inside valid bounds
    if(weight < -MAX_WEIGHT_VALUE)  weight = -MAX_WEIGHT_VALUE;
    else if(weight > MAX_WEIGHT_VALUE)  weight = MAX_WEIGHT_VALUE;

    //Set the synapse's weight
    node.incomingSynapses.at(synapseSourceIndex) = weight;
}

void NeuralNetAI::setNodeValue(int nodeIndex, float value)
{
    if(nodeIndex==1) return;   //Skip bias node
    if(2 <= nodeIndex && nodeIndex < 2+INPUT_SIZE) return;   //Skip input nodes

    if(nodeIndex<0 || nodeIndex>=NUMBER_OF_NODES) return;

    if(value < -MAX_NODE_VALUE)
    {
        value = -MAX_NODE_VALUE;
    }
    else if(value > MAX_NODE_VALUE)
    {
        value = MAX_NODE_VALUE;
    }

    m_nodes.at(nodeIndex).value = value;
}

void NeuralNetAI::setInput(const vector<float>& input)
{
    const int INPUT_START_INDEX = 2;
    for(int i=0; i<INPUT_SIZE; ++i)
    {
        m_nodes.at(INPUT_START_INDEX+i).value = input.at(i);
    }
}

float NeuralNetAI::function(const float x)
{
    /// Function
    float y = coreFunction(x);

    /// Make sure y is valid
    if(y < -OUTPUT_AMPLITUDE)
    {
        return -OUTPUT_AMPLITUDE;
    }

    if(y > OUTPUT_AMPLITUDE)
    {
        return OUTPUT_AMPLITUDE;
    }

    return y;
}

float NeuralNetAI::coreFunction(const float x)
{
    /// Function
    return x;
}

bool NeuralNetAI::triggered()
{
    return (m_nodes.at(0).value >= 1.f);
}

/**
*** Node[0] = 0 (Trigger)
*** Node[1] = 1 (Bias)
**/
void NeuralNetAI::resetNodesValues()
{
    for(Node& node : m_nodes)
    {
        node.value = INIT_NODE_VALUE;
    }

    m_nodes.at(0).value = 0.f; //Trigger
    m_nodes.at(1).value = 1.f; //Bias
}

void NeuralNetAI::debug()
{
    //*
    cout<<"Nodes:\t";
    for(int i=0; i<NUMBER_OF_NODES; ++i)
    {
        cout<<m_nodes[i].value<<"\t";
    }
    cout<<endl;

    cout<<"Weights:"<<endl;
    for(int i=0; i<NUMBER_OF_NODES; ++i)
    {
        for(int j=0; j<NUMBER_OF_NODES; ++j)
        {
            auto& synapses = m_nodes.at(j).incomingSynapses;
            auto synapse = synapses.find(i);
            if(synapse != synapses.end()) //If synapse exists
            {
                cout<<"\t"<<m_nodes.at(j).incomingSynapses.at(i);
            }
            else
            {
                cout<<"\t@";
            }
        }
        cout<<endl;
    }
    cout<<endl;
    //*/
}
