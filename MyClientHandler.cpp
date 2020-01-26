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
    // read info
    while ((r = read(client_socket, buffer, 1024))) {
        buffer[r] = 0;
        string curS = string(buffer);
        clientData.push_back(curS);
        if (!curS.rfind("end", 0))// if it starts with end
            break;
    }
    // check if we solve it already
    string convert = convertMatrixToString(clientData);
    if(this->m_cacheManager->haveSolution(convert))
    {
         //get the solution from cache manger
        string res = this->m_cacheManager->getSolution(convert);
         //send it
        send(client_socket, res.c_str(), res.length(), 0);
        return;
    }
    else { // if its the first we sendolve it, and then save it in cache manger.
         //solve it
        string res = this->m_solver->solve(clientData);
        //cout << res << endl;
        // save it
        this->m_cacheManager->saveSolution(convert, res);
        // send the solution
        send(client_socket, res.c_str(), res.length(), 0);
    }
}
/*convert matrix to string so we will store it in cache manger*/
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
