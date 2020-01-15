//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//
#include <string>
#include <vector>
#include "MyClientHandler.h"
#include "Matrix.h"

using namespace std;
MyClientHandler::MyClientHandler(Solver<std::vector<string>, string> *solver, CacheManager<vector<string>, string> *cacheManager_) {
    this->s = solver;
    this->cacheManager = cacheManager_;
}
void MyClientHandler::handleClient(int client_socket) {
    //********** move it from server
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

    std::string res = cacheManager->get(clientData);
    if (res.compare(""))
        return;
    cacheManager->put(clientData, s->solve(clientData));
}