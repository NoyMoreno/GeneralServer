//
// Created by noy on ١١‏/١‏/٢٠٢٠.
//

#include "Server.h"
#include "ClientHandler.h"
#include <stdio.h>
#include <bits/socket.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>

using namespace std;
namespace server_side {

    bool Server::open(int port ,ClientHandler *clientHandler) {
        //create socket
        int socketfd = socket(AF_INET, SOCK_STREAM, 0);
        if (socketfd == -1) {
            //error
            std::cerr << "Could not create a socket"<<std::endl;
            return -1;
        }

        //bind socket to IP address
        // we first need to create the sockaddr obj.
        sockaddr_in address; //in means IP4
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
        address.sin_port = port;

        //the actual bind command
        if (bind(socketfd, reinterpret_cast<struct sockaddr *>(&address), sizeof(address)) == -1) {
            std::cerr<<"Could not bind the socket to an IP"<<std::endl;
            return -2;
        }

        //making socket listen to the port
        if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
            std::cerr<<"Error during listening command"<<std::endl;
            return -3;
        } else{
            std::cout<<"Server is now listening ..."<<std::endl;
        }

        // accepting a client
        int client_socket = accept(socketfd, (struct sockaddr *)&address,
                                   (socklen_t*)&address);

        if (client_socket == -1) {
            std::cerr<<"Error accepting client"<<std::endl;
            return -4;
        }
        close(socketfd); //closing the listening socket

        cout << "Connection made!" << endl;
        thread t(this->runServer, client_socket, &fClose, close_mutex);
        t.detach();
        return 1;
    }
    void Server::runServer(int client_socket, Solver *s, bool *pClose, std::mutex &close_mutex) {
        close_mutex.lock();
        *pClose = true;
        close_mutex.unlock();

        //reading from client
        char buffer[1024] = {0};
        while (1) {
            int valread = read(client_socket, buffer, 1024);
            s->solve(buffer);

            close_mutex.lock();
            if (*pClose)
                break;
            close_mutex.unlock();
        }
        close_mutex.unlock();
        close(client_socket);
    }
    void Server::stop() {
        close_mutex.lock();
        fClose = true;
        close_mutex.unlock();
    }
}
