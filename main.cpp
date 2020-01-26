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
#include "MatrixSearchSolver.h"
#include "MyParallelServer.h"
#include "Server.h"

using namespace std;
using namespace server_side;
    int main(int args, char *argv[]) {
        int port = 5600;
        if (args >= 2)
            port = stoi(argv[1]);
        else 
            cout << "No argument received - using port 5600" << endl;

        string s = argv[0];
        Solver<vector < string>, string > *solver = new MatrixSearchSolver();
        //CacheManager<vector<string>, string> *cacheManager = new CacheManager<vector<string>, string>(new MyStringConverter());
        CacheManager<string, string> *cacheManager = new FileCacheManager();
        ClientHandler *clientHandler = new MyClientHandler(solver, cacheManager);

        //int port = atoi(argv[0]);
        Server *server = new MyParallelServer();
        server->open(port, clientHandler);

        delete (solver);
        delete (cacheManager);
        delete (clientHandler);

        return 0;
    }