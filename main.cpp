#include <iostream>
#include "Server.h"
#include "SerialServer.h"
#include "MyTestClientHandler.h"
#include "Solver.h"
int main() {
    SerialServer *server = new SerialServer("127.0.0.1");
    StringReverserSolver *solver = new StringReverserSolver();
    MyTestClientHandler *handler = new MyTestClientHandler(solver);
    server->open(5400, handler);
    delete server;
}