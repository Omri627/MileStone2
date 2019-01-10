cmake_minimum_required(VERSION 3.13)
project(project2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-pthread")

add_executable(project2 main.cpp Server.h ClientHandler.cpp ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.h CacheManager.h StringReverserSolver.cpp StringReverserSolver.h SerialServer.cpp SerialServer.h Searchable.h Searcher.h State.h Dfs.h MazeGame.h ParallelServer.cpp ParallelServer.h Solution.cpp Solution.h SearcherSolution.cpp SearcherSolution.h SearcherSolver.h MyPriorityQueue.h BestFirstSearch.cpp BestFirstSearch.h)