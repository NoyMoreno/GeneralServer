#include <iostream>
#include "Solver.h"
#include "ClientHandler.h"
#include "MyClientHandler.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "Server.h"
#include "MySerialServer.h"


using namespace std;
using namespace server_side;
int main(int args, char *argv[]) {
   if (args < 2)
   {
      cout << "No argument receive\n" << endl;
//      return 0;
   }
   StringReverser solver;
   CacheManager<string, string> *cacheManager = new FileCacheManager();
   ClientHandler *clientHandler = new MyClientHandler(&solver, cacheManager);

   int port = 5400;

   //int port = atoi(argv[0]);
   Server *server = new MySerialServer(clientHandler);
   server->open(port, clientHandler);
}