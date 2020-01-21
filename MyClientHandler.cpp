//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//
#include <string>
#include <vector>
#include "MyClientHandler.h"
#include "Matrix.h"

using namespace std;
//Solver<std::vector<string>, string>
MyClientHandler::MyClientHandler(Solver<vector<string>, string> *solver, CacheManager<string, string> *cacheManager) {

    this->m_solver = solver;
    this->m_cacheManager = cacheManager;
}
void MyClientHandler::handleClient(int client_socket) {
    //reading from client - this vector will represent the matrix's rows
    vector<string> clientData;
    char buffer[1024] = {0};
    int r;
    while ((r = read(client_socket, buffer, 1024))) {
        buffer[r] = 0;
        string curS = string(buffer);
        clientData.push_back(curS);
        if (!curS.rfind("end", 0))// if it starts with end
            break;
    }
    // check if we solve it already
    this->m_cacheManager->haveSolution(convertMatrixToString(clientData));
    string res = this->m_solver->solve(clientData);
    cout << res << endl;


//    std::string res = cacheManager->get(clientData);
//    if (res.compare(""))
//        return;
//    cacheManager->put(clientData, s->solve(clientData));
}
//***********************************************************************************
string MyClientHandler::convertMatrixToString(vector<string> vector) {
    // concatenate row's matrix
    string s;
    for (unsigned i = 0; i < vector.size(); i++) {
        s += vector[i];
    }
    std::hash<std::string> hasher;
    std::string fname = "ServerCacheManager_" + std::to_string(hasher(s)) + ".txt";
    return fname;
}
