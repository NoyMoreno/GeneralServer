//
// Created by noy on ١٣‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_STRINGREVERSER_H
#define PROJECT2_STRINGREVERSER_H


#include <algorithm>
#include <iostream>
#include "Solver.h"
/*This class get string from user and revers it*/
class StringReverser : public Solver<std::string, std::string> {
public:
    virtual std::string solve(std::string problem) {
        // Swap character
        reverse(problem.begin(), problem.end());
        return problem;
    }
    ~StringReverser(){}
};


#endif //PROJECT2_STRINGREVERSER_H
