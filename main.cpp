#include <iostream>
#include "Server.h"
#include "SerialServer.h"
#include "MyTestClientHandler.h"
#include "Solver.h"
#include "SearcherSolver.h"
#include "Dfs.h"

int main() {
    SerialServer* server = new SerialServer("127.0.0.1");
    delete server;
}