//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//

#include "MyClientHandler.h"
MyClientHandler::MyClientHandler(Solver<string, string> *solver, CacheManager<string, string> *cacheManager_) {
    this->s = solver;
    this->cacheManager = cacheManager_;
}
void MyClientHandler::handelClient(int client_socket) {
    //********** move it from server
    //reading from client
    char buffer[1024] = {0};
    cout << "yay" << endl;
    while (1) {
        int valread = recv(client_socket, buffer, 1024, 0);
        if (valread > 0){
            cout << buffer << endl;
        }
        s->solve(buffer);
    }

//        close_mutex.lock();
//        if (*pClose)
//            break;
//        close_mutex.unlock();
//    }
//    close_mutex.unlock();
//    close(client_socket);
}