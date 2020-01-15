//
// Created by noy on ١٥‏/١‏/٢٠٢٠.
//

#include "Matrix.h"

Matrix::Matrix(int row, int column, std::vector<State<Cell, double> *> initials) {

}

State<Cell, double> *Matrix::getInitialState() {
    return nullptr;
}

bool Matrix::isGoalState(State<Cell, double> *state) {
    return false;
}

std::vector<State<Cell, double> *> Matrix::getAllPossibleStates(State<Cell, double> *state) {
    return std::vector<State<Cell, double> *>();
}
