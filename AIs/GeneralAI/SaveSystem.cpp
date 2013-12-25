#include "SaveSystem.h"

using namespace std;

bool SaveSystem::save(const string& fileName) const
{
    //Get memory to save
    vector<int> memory = getMemory();

    //Open saveFile
    ofstream saveFile;
    saveFile.open(fileName.data());
    if (!saveFile.is_open())
        return false;

    //Write memory in file
    for(unsigned int i=0; i<memory.size(); i++)
    {
        saveFile<<memory[i]<<' ';
    }

    saveFile.close();
    return true;
}

bool SaveSystem::load(const string& fileName)
{
    vector<int> memory;

    //Open saveFile
    ifstream saveFile;
    saveFile.open(fileName.data());
    if(!saveFile.is_open())
    {
        return false;
    }
    else
    {
        // Recreate memory from file
        int data;

        while(saveFile>>data)
        {
            memory.push_back(data);
        }

        saveFile.close();

        setMemory(memory);

        return true;
    }
}
