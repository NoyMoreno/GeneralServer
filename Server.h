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
    private:
        Solver *s;
        bool fClose = false;
        std::mutex close_mutex;

        static void runServer(int client_socket, Solver *s, bool *fClose, std::mutex &close_mutex);
    public:
        Server(Solver _s) : s(_s) {}
        bool open(int port, ClientHandler *clientHandler);
        void stop();
    };

}
#endif //SERVER_SIDE_SERVER_H
