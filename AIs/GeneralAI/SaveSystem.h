#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include <vector>
#include <string>
#include <fstream>

/**
*   SaveSystem provides an easy way to save data to a file and to load it later.
**/
class SaveSystem
{
    public:
        /**
        * Save system state in a file
        * Returns true if successful
        **/
        bool save(const std::string& fileName) const;

        /**
        * Load system state from a file
        * Returns true if successful
        **/
        bool load(const std::string& fileName);

    protected:
        /// Returns a vector<int> that represents the system state
        virtual std::vector<int> getMemory() const = 0;

        /// Load a system state from a vector<int>.
        virtual void setMemory(std::vector<int> memory) = 0;
};

#endif // SAVESYSTEM_H
