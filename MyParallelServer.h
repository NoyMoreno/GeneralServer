//
// Created by noy on ٢٢‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_MYPARALLELSERVER_H
#define PROJECT2_MYPARALLELSERVER_H

#include <thread>
#include <vector>
#include "Server.h"

class ClientHandler;

class MyParallelServer : public server_side::Server{
protected:
    int client_socket;
    int m_port;
    bool m_stop = false;
    bool connection_made = false;
public:
    MyParallelServer();
    bool open(int port, ClientHandler *clientHandler);
    void stop();
    ~MyParallelServer(){}

private:
    bool timeout = false;
    std::thread *m_t;
    std::thread *timout_thread;
    std::vector<std::thread*> threads;
    bool connected_once;
    //void HandleCommunication(int i);

    void HandleCommunication();
};


#endif //PROJECT2_MYPARALLELSERVER_H
