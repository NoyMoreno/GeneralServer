//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_MYCLIENTHANDLER_H
#define PROJECT2_MYCLIENTHANDLER_H


#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
using namespace std;

class MyClientHandler : public ClientHandler {
private:
    // ********************need to contain solver obj
    CacheManager<string, string> *cacheManager{};

public:


};


#endif //PROJECT2_MYCLIENTHANDLER_H
