#include "SaveSystem.h"

using namespace std;

void SaveSystem::save(const string& fileName) const
{
    //Open saveFile
    ofstream saveFile;
    saveFile.open(fileName.data());
    if (!saveFile.is_open())
    {
        throw fstream::failure("Unable to open file");
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
}

void SaveSystem::load(const string& fileName)
{
    //Open saveFile
    ifstream saveFile;
    saveFile.open(fileName.data());
    if(!saveFile.is_open())
    {
        throw fstream::failure("Unable to open file");
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

    //Our job is done, the AI subclasses will deal with the memory however they see fit
    setMemory(memory);
}
