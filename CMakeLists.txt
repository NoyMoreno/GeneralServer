cmake_minimum_required(VERSION 3.15)
project(Project2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(Project2 main.cpp Server.cpp Server.h Solver.cpp Solver.h ClientHandler.cpp ClientHandler.h MyClientHandler.cpp MyClientHandler.h MySerialServer.cpp MySerialServer.h CacheManager.cpp CacheManager.h ISearcher.cpp ISearcher.h ISearchable.cpp ISearchable.h State.cpp State.h StringReverser.cpp StringReverser.h FileCacheManager.cpp FileCacheManager.h AbstractSearcher.cpp AbstractSearcher.h MyPriorityQueue.cpp MyPriorityQueue.h BestFirstSearch.cpp BestFirstSearch.h Matrix.cpp Matrix.h StringConverter.cpp StringConverter.h MyStringConverter.cpp MyStringConverter.h MatrixSearchSolver.cpp MatrixSearchSolver.h Astar.h)

