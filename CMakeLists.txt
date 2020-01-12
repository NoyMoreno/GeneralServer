cmake_minimum_required(VERSION 3.15)
project(Project2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project2 main.cpp Server.cpp Server.h Solver.cpp Solver.h ClientHandler.cpp ClientHandler.h MyClientHandler.cpp MyClientHandler.h MySerialServer.cpp MySerialServer.h CacheManager.cpp CacheManager.h OA.cpp OA.h Searcher.cpp Searcher.h Searchable.cpp Searchable.h State.cpp State.h)