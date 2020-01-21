//
// Created by noy on ١٥‏/١‏/٢٠٢٠.
//

#include "Matrix.h"
#include <sstream>
#include <regex>
#include <iostream>

std::vector<double> parseLineToValues(std::string s) {
    std::vector<double> vec;
    std::stringstream ss(s);
    std::string token;
    // define trim regex
    std::regex trimR("^\\s+|\\s+$");
    while (std::getline(ss, token, ',')) {
        // trim spaces
        std::regex_replace(token, trimR, "");
        vec.push_back(std::stod(token));
    }
    return vec;
}

Matrix::Matrix(std::vector<std::string> input) {
    // parse the input
    // Go through each row, and parse it
    // The last 3 lines are - start_x,start_y - end_x,end_y - end\n
    int total_rows = input.size() - 3;

    // Go through and populate the matrix
    int iRow;
    for (iRow = 0; iRow < total_rows; iRow++) {
        // Get all the numbers
        std::vector<double> values = parseLineToValues(input[iRow]);
        for (unsigned iCol = 0; iCol < values.size(); iCol++) {
            if (values[iCol] != -1)
                _matrix[Cell(iRow, iCol)] = values[iCol];
        }
    }// next row

    // Get the start and end - the double of this cells is the i and the j
    std::vector<double> finalVals = parseLineToValues(input[input.size() - 3]);
    Cell c(finalVals[0], finalVals[1]);
    startCell = c;
    finalVals = parseLineToValues(input[input.size() - 2]);
    Cell c2(finalVals[0], finalVals[1]);
    endCell = c2;
}

State<Cell, double> Matrix::getInitialState() {
    return State<Cell, double>(startCell, _matrix[startCell]);
}
bool Matrix::isGoalState(State<Cell, double> state) {
    return state.getT() == endCell;
}

std::vector<State<Cell, double>> Matrix::getAllPossibleStates(State<Cell, double> state) {
    std::vector<State<Cell, double>> vec;
    Cell loc = state.getT();
    // What are our transformations?
    std::vector<std::pair<int, int>> transformations = {
            {-1, 0},
            {0, -1},
            {1, 0},
            {0, 1}
    };

    for (auto tp : transformations){
        // look up
        auto d = _matrix.find(Cell(loc.getI() + tp.first, loc.getJ() + tp.second));
        if (d != _matrix.end())
            vec.push_back(State<Cell, double>(d->first, d->second));
    }

    return vec;
}
State<Cell, double> Matrix::getGoalState() {
    return State<Cell, double>(endCell, _matrix[endCell]);
}
