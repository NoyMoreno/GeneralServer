//
// Created by noy on ١٥‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_MATRIX_H
#define PROJECT2_MATRIX_H

#include "ISearchable.h"

struct Cell {
private:
    int m_i;
    int m_j;
public:
    Cell(int i, int j){
        m_i = i;
        m_j = j;
    }
    int getI() {
        return m_i;
    }
    int getJ() {
        return m_j;
    }
};
class Matrix : ISearchable<Cell, double> {
    Matrix(int row, int column, std::vector<State<Cell, double>*> initials);
    //get initial state
    State<Cell, double > *getInitialState();
    // the end
    bool isGoalState(State <Cell, double > *state);
    //פונקציית המעברים
    std::vector<State<Cell, double >*> getAllPossibleStates(State<Cell, double > *state);
    ~Matrix(){

    }
};


#endif //PROJECT2_MATRIX_H
