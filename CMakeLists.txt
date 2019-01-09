cmake_minimum_required(VERSION 3.13)
project(project2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-pthread")

add_executable(project2 main.cpp Server.cpp Server.h ClientHandler.cpp ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.cpp Solver.h CacheManager.cpp CacheManager.h FileCacheManager.cpp StringReverserSolver.cpp StringReverserSolver.h SerialServer.cpp SerialServer.h Searchable.cpp Searchable.h Searcher.cpp Searcher.h State.cpp State.h Dfs.cpp Dfs.h MazeGame.cpp MazeGame.h ParallelServer.cpp ParallelServer.h BestFirstSearch.h BestFirstSearch.cpp Solution.cpp Solution.h SearcherSolution.cpp SearcherSolution.h MyPriorityQueue.cpp MyPriorityQueue.h)