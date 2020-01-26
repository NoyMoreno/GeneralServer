//
// Created by noy on ١٣‏/١‏/٢٠٢٠.
//
#include "FileCacheManager.h"
#include <fstream>
FileCacheManager ::FileCacheManager() {}
bool FileCacheManager::haveSolution(string problem)
{
    std::ifstream file(problem);
    if(file.is_open()) {
        file.close();
        return true;
    } else {
        return false;
    }
}
// get the solution. The user have to check if the solution isSaved cameFrom get it.
string FileCacheManager::getSolution(string problem)
{
    string line;
    ifstream myfile (problem);
    if (myfile.is_open())
    {
        getline (myfile,line);
         myfile.close();
    }
    else cout << "Unable to open file";
    return line;
}
// save the solution to the problem
void FileCacheManager:: saveSolution(string problem, string solution)
{
    std::fstream fs;
    fs.open (problem, std::fstream::in | std::fstream::out | std::fstream::app);
    fs << solution;
    fs.close();
}
