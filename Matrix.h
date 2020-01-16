//
// Created by noy on ١٥‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_MATRIX_H
#define PROJECT2_MATRIX_H

#include "ISearchable.h"
#include <string>
#include <unordered_map>

class Cell {
private:
    int m_i;
    int m_j;
public:
    Cell(){}
    Cell(int i, int j){
        m_i = i;
        m_j = j;
    }
    int getI() const {
        return m_i;
    }
    int getJ() const {
        return m_j;
    }
};
inline bool operator==(Cell c1, Cell c2) {
    return c1.getI() == c2.getI() && c1.getJ() == c2.getJ();
}

struct CellHash {
    size_t operator()(const Cell &c) const {
        return ((size_t)c.getI() << 32) | c.getJ();
    }
};

class Matrix : public ISearchable<Cell, double> {
private:
    Cell startCell, endCell;
    std::unordered_map<Cell, double, CellHash> _matrix;
public:
    Matrix(std::vector<std::string> s);
    //get initial state
    State<Cell, double> getInitialState();
    // the end
    bool isGoalState(State<Cell, double> state);
    //פונקציית המעברים
    std::vector<State<Cell, double>> getAllPossibleStates(State<Cell, double> state);
    // convert problem to string
    std::string problemToString(std::vector<std::string> matrixAsDataClient);

    ~Matrix() {
    }
};


#endif //PROJECT2_MATRIX_H
