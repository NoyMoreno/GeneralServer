#include <iostream>
#include "Solver.h"
#include "ClientHandler.h"
#include "MyClientHandler.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "Server.h"
#include "MySerialServer.h"
#include "ISearchable.h"
#include "BestFirstSearch.h"
#include "ISearcher.h"
#include "MyStringConverter.h"
#include "MatrixSearchSolver.h"
#include "Server.h"

using namespace std;
using namespace server_side;
int main(int args, char *argv[]) {
   if (args < 2)
   {
      cout << "No argument receive\n" << endl;
//      return 0;
   }
   MatrixSearchSolver solver;
   //CacheManager<vector<string>, string> *cacheManager = new CacheManager<vector<string>, string>(new MyStringConverter());
   CacheManager<string,string> *cacheManager = new FileCacheManager();
   ClientHandler *clientHandler = new MyClientHandler(&solver, cacheManager);

   int port = 5600;

   //int port = atoi(argv[0]);
   Server *server = new MySerialServer(clientHandler);
   server->open(port, clientHandler);
}