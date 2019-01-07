#ifndef CLIENT_HANDLER
    #define CLIENT_HANDLER

#include <iostream>
class Server;
using namespace std;
class ClientHandler {
public:
    virtual void handleClient(string problem, Server * server) = 0;
};


#endif //PROJECT2_CLIENTHANDLER_H
