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
#include "Astar.h"
#include "BreadthFirstSearch.h"
#include "DepthFirstSearch.h"
#include "BestFirstSearch.h"

class MatrixSearchSolver : public Solver<std::vector<std::string>, std::string> {
public:
    std::string solve(std::vector<std::string> problem) {
        // Parse the matrix
        Matrix m(problem);
        std::cout << "finished matrix..." << std::endl;
        // Run best first
        BestFirstSearch<Cell, double> bfs;
        auto res = bfs.search(&m);
        std::cout << bfs.getNumberOfNodesEvaluated() << std::endl;

        std::stringstream s;
        // convert to down/up/right/left
        for (auto state : res) {
            s << "(" << state.getT().getI() << "," << state.getT().getJ() << ") [" << state.getC() << "]" << std::endl;
        }
        return s.str();
    }
    ~MatrixSearchSolver() {}
};


#endif //PROJECT2_MATRIXSEARCHSOLVER_H
