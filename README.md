# GeneralServer

A Server with multiple matrix-search algorithms accepting and handling multiple requests in parallel.

## About the code

In this code, we implement the general structure of the server with generics, and then further implement our specific server by inheriting from those classes and adding types.
The server side of the code is built of 4 main components:
 - Server
 - Client Handler
   - Solver
   - Cache Manager
 
The server is a generic class that defines the base functions needed for a server to operate (open, handle, close). Inheriting from that class we implemented two specific kinds of servers: The SerialServer and the ParallelServer. The SerialServer accepts one request at a time, processes it, and then is ready to accept a new one. The ParallelServer accepts in parallel as many requests as needed, and open a new thread for each one of the requests, and returns whenever it finishes.
The ClientHandler is a generic component which gets notified when there is a request from a client, reads in the request, handles it according to a specific module, and returns the answer. 
Within the ClientHandler, we have two more components:
- The first is the Solver. When implementing a specific handler, we define the type of input and type of output, but in addition we need some algorithm which will take the input and return the answer. That is the solver. It is a generically defined class with the input/output functions, and each algorithm inherits from this class and implements a search in it's own way.
- The second is the CacheManager. In order to avoid duplication, whenever we get a request and solve it, we save the result to a unique file, and then if the same input is requested again, we already saved how to solve it so we don't processing power solving it again.
  - The CacheManager is a generic class, and we implemented a FileCacheManager which saves it to the file.
  
  
## The Solvers
  
  The task at hand is given a matrix of weights, find the path from one point to another. 
  We implemented a few different algorithms for search:
  
  
#### BestFirstSearch
  
  [Wikipedia Page](https://en.wikipedia.org/wiki/Best-first_search)
  
  This algorithm goes through all possible paths from each point, giving priority to the shortest path available, and finds the cheapest path from point A to point B.
  
#### BreadthFirstSearch
  [Wikipedia Page](https://en.wikipedia.org/wiki/Breadth-first_search)
  
  This algorithm does a breadth-wide search, going through all the options at each point trying to find the shorted path from point A to point B, searching wide.
  
#### DepthFirstSearch
  [Wikipedia Page](https://en.wikipedia.org/wiki/Depth-first_search)
  
  This algorithm does a depth-wide search, going through all the options at each point trying to find the shorted path from point A to point B, searching deep.

#### AStarSearch
  [Wikipedia Page](https://en.wikipedia.org/wiki/A*_search_algorithm)
  
  This algorithm is similar to the Best-First-Search method, but the weights have an additional factor of taking into account the distance of the current point from the end-point, in order to give priority to shorter paths and have a faster search.
