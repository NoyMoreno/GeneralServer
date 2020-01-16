//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_MYCLIENTHANDLER_H
#define PROJECT2_MYCLIENTHANDLER_H

#include <stdio.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "Matrix.h"
#include <vector>
using namespace std;

class MyClientHandler : public ClientHandler {
protected:
    //Solver<vector<string>, string> *m_solver;
    Solver<ISearchable<Cell, double> *, vector<State<Cell, double>>> *m_solver;
    CacheManager<string, string> *m_cacheManager;
public:
    MyClientHandler(Solver<ISearchable<Cell, double> *, vector<State<Cell, double>>> *solver, CacheManager<string, string> *cacheManager_);
    void handleClient(int socket);

    string convertMatrixToString(vector<string> vector);
};


#endif //PROJECT2_MYCLIENTHANDLER_H
