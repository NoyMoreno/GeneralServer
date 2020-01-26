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
        int preI = res.at(0).getT().getI();
        int preJ = res.at(0).getT().getJ();
        std::string solution;
        for (auto cur : res )
        {
            int curI = cur.getT().getI();
            int curJ = cur.getT().getJ();
            if (curI > preI)
            {
               solution += "Down,";
            }
            if (curI < preI)
            {
                solution += "Up,";
            }
            if (curJ > preJ)
            {
                solution += "Right,";
            }
            if (curJ < preJ)
            {
                solution += "Left,";
            }
            // next
            preI = curI;
            preJ = curJ;
        }
        // delete the last ,
        solution.erase(solution.length() - 1, 1);
        return solution;

//      for (auto state : res) {
//            s << "(" << state.getT().getI() << "," << state.getT().getJ() << ") [" << state.getC() << "]" << std::endl;
//        }

        return s.str();
    }
    ~MatrixSearchSolver() {}
};


#endif //PROJECT2_MATRIXSEARCHSOLVER_H
