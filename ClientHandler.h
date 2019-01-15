#ifndef CLIENT_HANDLER
    #define CLIENT_HANDLER

#include <iostream>

class Client;
class Server;
using namespace std;
class ClientHandler {
public:
    /**
    * handleClient method gets a server and client.
    * and aid the server to handle client request.
    * for any searchable problems, this method processed the data regarding the problem
    * and produce a solution.
    * @param server server object
    * @param client client object
    * @return returns 1 if the this method handle client requests successfully
    * returns 0 if error occured.
    */
    virtual int handleClient(Server * server, Client* client) = 0;
    /**
    * desructor, used to free memory.
    */
    virtual ~ClientHandler();
};


#endif