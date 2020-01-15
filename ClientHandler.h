//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_CLIENTHANDLER_H
#define PROJECT2_CLIENTHANDLER_H


#include <string>

class ClientHandler {
public:
    virtual void handleClient(int socket) = 0;
};


#endif //PROJECT2_CLIENTHANDLER_H
