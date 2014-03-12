#include "SaveSystem.h"

using namespace std;

bool SaveSystem::save(const string& fileName) const
{
    //Open saveFile
    ofstream saveFile;
    saveFile.open(fileName.data());
    if (!saveFile.is_open())
    {
        return false;   //Failure
    }

    //Get memory to be saved
    vector<int> memory = getMemory();

    //Write memory in file
    for(unsigned int i=0; i<memory.size(); i++)
    {
        saveFile<<memory[i]<<' ';
    }

    //Close file
    saveFile.close();

    return true;    //Success
}

bool SaveSystem::load(const string& fileName)
{
    //Open saveFile
    ifstream saveFile;
    saveFile.open(fileName.data());
    if(!saveFile.is_open())
    {
        return false;   //Failure
    }

    // Recreate memory from file
    vector<int> memory;
    int data;

    while(saveFile>>data)
    {
        memory.push_back(data);
    }

    //Close file
    saveFile.close();

    //Job's done!
    setMemory(memory);

    return true;    //Success
}
