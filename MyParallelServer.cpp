//
// Created by noy on ٢٢‏/١‏/٢٠٢٠.
//

#include "MyParallelServer.h"

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
#include <chrono>
#include <future>

using namespace std;
MyParallelServer::MyParallelServer() : server_side::Server(){}
//bool MySerialServer::open(int port, ClientHandler *clientHandler) {
//    this->HandleCommunication(port);
//    while (!this->m_stop) {
//        socketfd = accept(socketfd, (struct sockaddr *) &client_address,
//                                                (socklen_t *) &len);
//        if (socketfd < 0) {
//            if (errno == EWOULDBLOCK) {
//                if (connection_made) {
//                    // first communication
//                    continue;
//                }
//                cout << "timeout!" << endl;
//                break;
//            } else {
//                perror("other error");
//            }
//        }
//        connection_made = false;
//        //handle client, when finished, move on to the next client.
//        this->m_clientHandler->handleClient(socketfd);
//    }
//    //server closed
//    close(socketfd);
//}
//
//void MySerialServer::stop()
//{
//    this->m_stop = true;
//}

bool MyParallelServer::open(int port, ClientHandler *clientHandler) {
    m_port = port;
    m_clientHandler = clientHandler;
    std::mutex m;
    std::condition_variable cv;
    int retValue;
    connected_once = false;

    m_t = new thread([&cv,this]()
                               {
                                   this->HandleCommunication();
                                   cv.notify_one();
                               });

//    timout_thread = new thread([this]()
//                     {
//                        std::this_thread::sleep_for(2s);
//                         if (!connected_once){
//                             stop();
//                            // put here code that causes the m_t thread to terminate
//                         }
//                     });
    m_t->join();
    stop();
    {
        std::unique_lock<std::mutex> l(m);
        if(cv.wait_for(l, 10s) == std::cv_status::timeout)
            return false;
        // this->stop();
        //throw std::runtime_error("Timeout");
    }

//    m_port = port;
//    m_t = new thread([this]{this->HandleCommunication();});
//
//    if (m_t == nullptr)
//    {
//        return false;
//    }
//    m_t->join();
//    this->stop();
}
void MyParallelServer::stop()
{
    if (m_t != nullptr)
    {
        delete(m_t);
    }
    for (std::vector<std::thread*>::iterator iter = threads.begin(); iter != threads.end();++iter)
    {
        delete *iter;
    }
}

void MyParallelServer::HandleCommunication()
{
    cout << "hii" << endl;
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return;
    }
    /*size_t t1 = 2, t2 = sizeof(int);
    setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, &t1, t2);*/
    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(m_port);

    //the actual bind command
    if (bind(socketfd, reinterpret_cast<struct sockaddr *>(&address), sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        return;
    }
    //making socket listen to the port
    if (listen(socketfd, 5) == -1) {
        std::cerr<<"Error during listening command"<<std::endl;
        return;
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }


    while (true)
    {
        socklen_t len = sizeof(address);
        future<int> accept_thread = async(accept, socketfd, (struct sockaddr *) &address,
                                          (socklen_t *) &len);
        client_socket = accept_thread.get();
        cout << "accepted a client!!!" << endl;
        try {
//            socklen_t len = sizeof(address);
//            future<int> accept_thread = async(accept, socketfd, (struct sockaddr *) &address,
//                                              (socklen_t *) &len);

            if (client_socket == -1) {
                std::cerr << "Error accepting client" << std::endl;
                return;
            }

            connected_once = true;
            cout << "Connection made!" << endl;
            // We separated communication from the way we communicate.
            //In this function we will begin to communicate

            // For the parallel open a thread here.
            std::thread* t = new thread([this]()
                             {
                                int c = client_socket;
                                 m_clientHandler->handleClient(c);
                                 close(c);
                             });
            threads.push_back(t);
        }
        catch(std::runtime_error& e) {
            std::cout << e.what() << std::endl;
            this->timeout = true;
        }


    }
}
