#ifndef CLIENT_HANDLER
    #define CLIENT_HANDLER

#include <iostream>

class Client;
class Server;
using namespace std;
class ClientHandler {
public:
    virtual int handleClient(Server * server, Client* client) = 0;

    virtual ~ClientHandler();
};


#endif