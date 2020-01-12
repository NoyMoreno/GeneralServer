//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_MYSERIALSERVER_H
#define PROJECT2_MYSERIALSERVER_H

#include "Server.h"

class MySerialServer : public server_side::Server {
public:
    // listening to port - we already done it ?
    void start(int port);
};


#endif //PROJECT2_MYSERIALSERVER_H
