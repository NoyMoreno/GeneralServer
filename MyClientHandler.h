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
#include <vector>
using namespace std;

class MyClientHandler : public ClientHandler {
protected:
    Solver<vector<string>, string> *s;
    CacheManager<vector<string>, string> *cacheManager;
public:
    MyClientHandler(Solver<vector<string>, string> *solver, CacheManager<vector<string>, string> *cacheManager_);
    void handleClient(int socket);

};


#endif //PROJECT2_MYCLIENTHANDLER_H
