//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_MYSERIALSERVER_H
#define PROJECT2_MYSERIALSERVER_H

#include "Server.h"

//namespace std
//{
//    class thread;
//}

class MySerialServer : public server_side::Server {
protected:
    int m_port;
    bool m_stop = false;
    bool connection_made = false;
public:
    MySerialServer();
    bool open(int port, ClientHandler *clientHandler);
    void stop();
    ~MySerialServer(){}

private:
    bool timeout = false;
    std::thread *m_t;
    //void HandleCommunication(int i);

    void HandleCommunication();
};


#endif //PROJECT2_MYSERIALSERVER_H
