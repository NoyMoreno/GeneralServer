//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_SOLVER_H
#define PROJECT2_SOLVER_H
#include <string>

template <typename P, typename S>
class Solver {
public:
    virtual S solve(P problem) = 0;
};


#endif //PROJECT2_SOLVER_H
