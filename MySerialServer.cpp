//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//
#include "Server.h"
#include "ClientHandler.h"
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
//#include <thread>
#include "MySerialServer.h"
using namespace std;
MySerialServer::MySerialServer(ClientHandler *clientHandler_) : server_side::Server(clientHandler_){}
bool MySerialServer::open(int port, ClientHandler *clientHandler) {
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
    address.sin_port = htons(port);

    //the actual bind command
    if (bind(socketfd, reinterpret_cast<struct sockaddr *>(&address), sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        return -2;
    }
    //making socket listen to the port
    if (listen(socketfd, 5) == -1) {
        std::cerr<<"Error during listening command"<<std::endl;
        return -3;
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }
    // accepting a client
    socklen_t len = sizeof(address);
    int client_socket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t*)&len);

    cout << "accepted a client!!!" << endl;
    if (client_socket == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
        return -4;
    }
    close(socketfd); //closing the listening socket

    cout << "Connection made!" << endl;
//    stop();
    // We separated communication from the way we communicate.
    //In this function we will begin to communicate
    clientHandler->handleClient(client_socket);
    close(client_socket);
//    thread t(this->runServer, client_socket, &fClose, close_mutex, clientHandler);
//    t.detach();
    return 1;
}
void MySerialServer::stop() {
    close_mutex.lock();
    fClose = true;
    close_mutex.unlock();
}