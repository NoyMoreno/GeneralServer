//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//
#include "Server.h"
#include "ClientHandler.h"
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <future>
#include "MySerialServer.h"

using namespace std;
MySerialServer::MySerialServer() : server_side::Server(){}

bool MySerialServer::open(int port, ClientHandler *clientHandler) {
    m_port = port;
    m_clientHandler = clientHandler;
    m_t = new thread([this]() {
          this->HandleCommunication();
    });
    //m_t->detach();
    while (1) {
        std::mutex m;
        unique_lock<mutex> l(m);
        auto out = cv.wait_for(l, chrono::seconds(10));
        if (out == std::cv_status::timeout) {
            if (m_stop) break;
            close(socketfd);
            cout << "Timeout waiting for client... exiting" << endl;
            return false;
        }
        if (m_stop)
            break;
        // wait for it to finish the current request - give it 45 seconds
        cv.wait_for(l, chrono::seconds(45));
    }
    delete(m_t);
    return true;
}
void MySerialServer::stop() {
    close(socketfd);
    m_stop = true;
}

void MySerialServer::HandleCommunication() {
    //create socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        m_stop = true;
        cv.notify_one();
        return;
    }
    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(m_port);

    //the actual bind command
    if (bind(socketfd, reinterpret_cast<struct sockaddr *>(&address), sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        m_stop = true;
        cv.notify_one();
        close(socketfd);
        return;
    }
    //making socket listen to the port
    if (listen(socketfd, 5) == -1) {
        std::cerr<<"Error during listening command"<<std::endl;
        m_stop = true;
        cv.notify_one();
        close(socketfd);
        return;
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }


    while (true) {
        socklen_t len = sizeof(address);
        int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &len);
        cv.notify_one();
        //cout << "accepted a client!!!" << endl;
        try {
           if (client_socket == -1) {
               std::cerr << "Error accepting client" << std::endl;
               close(socketfd);
               return;
          }
            // We separated communication from the way we communicate.
            //In this function we will begin to communicate

            // For the parallel open a thread here.
            m_clientHandler->handleClient(client_socket);
            close(client_socket);

            cv.notify_one();
        }
        catch(std::runtime_error& e) {
            cout << "Timeout" << endl;
            std::cout << e.what() << std::endl;
            this->m_stop = true;
            cv.notify_one();
            close(socketfd);
            return;
        }

    }
}