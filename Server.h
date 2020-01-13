//
// Created by noy on ١١‏/١‏/٢٠٢٠.
//

#ifndef SERVER_SIDE_SERVER_H
#define SERVER_SIDE_SERVER_H

#include <string>
#include <mutex>
#include "Solver.h"
#include "ClientHandler.h"

namespace server_side {
    class Server {
    protected:
        bool fClose;
        std::mutex close_mutex;
        ClientHandler *m_clientHandler;
        //static void runServer(int client_socket, bool *fClose, std::mutex &close_mutex);
    public:
        Server(ClientHandler *clientHandler) : fClose{false}, close_mutex{},
                                               m_clientHandler{clientHandler}
        {
            if(clientHandler == nullptr)
            {
                throw;
            }
        }
        virtual bool open(int port, ClientHandler *clientHandler) = 0;
        virtual void stop() = 0;
    };

}
#endif //SERVER_SIDE_SERVER_H
