//
// Created by noy on ١٥‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_MATRIXSEARCHSOLVER_H
#define PROJECT2_MATRIXSEARCHSOLVER_H

#include "Solver.h"
#include <vector>
#include <string>
#include <sstream>
#include "Matrix.h"
#include "BestFirstSearch.h"

class MatrixSearchSolver : public Solver<std::vector<std::string>, std::string> {
public:
    std::string solve(std::vector<std::string> problem) {
        // Parse the matrix
        Matrix m(problem);
        // Run best first
        BestFirstSearch<Cell, double> bfs;
        auto res = bfs.search(&m);


        std::stringstream s;
        // convert to down/up/right/left
        for (auto state : res) {
            s << "(" << state.getT().getI() << "," << state.getT().getJ() << ") [" << state.getC() << "]" << std::endl;
        }
        return s.str();
    }
};


#endif //PROJECT2_MATRIXSEARCHSOLVER_H
