//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//
#include <string>
#include <vector>
#include "MyClientHandler.h"
#include "Matrix.h"

using namespace std;
//Solver<std::vector<string>, string>
MyClientHandler::MyClientHandler(Solver<ISearchable<Cell, double> *, vector<State<Cell, double>>> *solver, CacheManager<string, string> *cacheManager) {

    this->m_solver = solver;
    this->m_cacheManager = cacheManager;
}
void MyClientHandler::handleClient(int client_socket) {
    //reading from client - this vector will represent the matrix's rows
    vector<string> clientData;
    int buf_idx = 0;
    char buffer[1024] = {0};
    while (read(client_socket, buffer, 1024)) {
        string curS = string(buffer);
        clientData.push_back(curS);
        if (!curS.rfind("end", 0))// if it starts with end
            break;
    }
    // creat Matrix as searchable
    ISearchable<Cell, double> *matrix = new Matrix(clientData);
    // check if we solve it already
    this->m_cacheManager->haveSolution(convertMatrixToString(clientData));
    std::vector<State<Cell, double>> res = this->m_solver->solve(matrix);


//    std::string res = cacheManager->get(clientData);
//    if (res.compare(""))
//        return;
//    cacheManager->put(clientData, s->solve(clientData));
}
***********************************************************************************
string MyClientHandler::convertMatrixToString(vector<string> vector) {
    // concatenate row's matrix
    ////string matrixAsString

}
