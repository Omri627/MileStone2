#ifndef CLIENT_HANDLER
    #define CLIENT_HANDLER

#include <iostream>
class Server;
using namespace std;
class ClientHandler {
public:
    virtual int handleClient(Server * server) = 0;

    virtual ~ClientHandler();
};


#endif