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
using namespace std;

class MyClientHandler : public ClientHandler {
protected:
    Solver<string, string> *s;
    CacheManager<string, string> *cacheManager;
public:
    MyClientHandler(Solver<string, string> *solver, CacheManager<string, string> *cacheManager_);
    void handelClient(int socket);

};


#endif //PROJECT2_MYCLIENTHANDLER_H
