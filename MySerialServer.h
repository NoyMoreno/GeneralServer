//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_MYSERIALSERVER_H
#define PROJECT2_MYSERIALSERVER_H

#include "Server.h"

class MySerialServer : public server_side::Server {
public:
    MySerialServer(ClientHandler *clientHandler_);
    bool open(int port, ClientHandler *clientHandler);
    void stop();
};


#endif //PROJECT2_MYSERIALSERVER_H
