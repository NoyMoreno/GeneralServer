//
// Created by noy on ١٣‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_FILECACHEMANAGER_H
#define PROJECT2_FILECACHEMANAGER_H


#include <string>
#include <unordered_map>
#include "CacheManager.h"

class FileCacheManager : public CacheManager <string, string> {
public:
    FileCacheManager();
    // check if the solution already exist.
     bool haveSolution(string problem);

    // get the solution. The user have to check if the solution isSaved cameFrom get it.
    string getSolution(string problem);

    // save the solution to the problem
    void saveSolution(string problem, string solution);

    //add pair of problem and his solution to file
    void addToFile(string problem, string solution);

    // write the info
    void WriteToFile(bool toAppend, string problem, string solution);
    ~FileCacheManager(){}
};


#endif //PROJECT2_FILECACHEMANAGER_H
