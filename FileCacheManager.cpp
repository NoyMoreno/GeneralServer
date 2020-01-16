//
// Created by noy on ١٣‏/١‏/٢٠٢٠.
//
#define FILE_NAME ("File_ProblemsToSolutions")
#include "FileCacheManager.h"
#include <fstream>
FileCacheManager ::FileCacheManager() {}
void FileCacheManager:: addToFile(string problem, string solution)
{
    std::ofstream file(FILE_NAME);
    if(file) {
        WriteToFile(true, problem, solution);
    } else {
        WriteToFile(false, problem, solution);
    }
}
bool FileCacheManager::haveSolution(string problem)
{
    // If key not found in map
    if (this->problemsToSolutions_map.find(problem) == problemsToSolutions_map.end())
        return false;
    return true;
}
// get the solution. The user have to check if the solution isSaved cameFrom get it.
string FileCacheManager::getSolution(string problem)
{
    return this->problemsToSolutions_map[problem];
}
// save the solution to the problem
void FileCacheManager:: saveSolution(string problem, string solution)
{
    this->problemsToSolutions_map[problem] = solution;
}
void WriteToFile(bool toAppend, string problem, string solution)
{
    std::ofstream file;
    /* Use append or write flag. */
    if (toAppend == true)
    {
        //add to end of file
        file.open(FILE_NAME, std::ios_base::app);
    } else
    {
       // Open for input operations.
        file.open(FILE_NAME, std::ios::in);
    }
    if(file.is_open())
    {
        file << problem << " : " << solution << "\n"<<endl;
    } else {
        cout << "Could not open the file\n" << endl;
        throw;
    }
}