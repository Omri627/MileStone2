#ifndef SERVER
    #define SERVER

#include "ClientHandler.h"
#include "Client.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string>

#define END "end"
extern pthread_mutex_t global_mutex;
/* mutex object used to lock and unlock chunk of code  */
using namespace std;
class Server {
public:
    /* parameters for create server method */
    struct create_params {
        Server* server;
        int port;
        int* socketFd;
    };
    /**
     * createPortConnection method create connection to specific port
     * and returns the file descriptor of this port connection.
     * @param port port number
     * @return returns file descriptor of port connection
     */
    virtual int createPortConnection(int port);
    /**
     * readData method gets a client that connected to server,
     * and reads the data given by this client.
     * @param client client object.
     * @return returns the data received by given client.
     */
    virtual string readData(Client* client);

    /**
     * sendData method gets a message and client which connected to server
     * the method send the client the given message.
     * @param data data/message
     * @param client specific client
     */
    virtual void sendData(string data, Client* client);
    /**
     * open method open a connection in given port.
     * when a client connect in this port to the server,
     * interact with client and solve his input problems.
     * @param port port of connection
     * @param clientHandler aid the server to solve client problems.
     */
    virtual void open(int port, ClientHandler* clientHandler) = 0;
    /**
    * static method which execute create port connection method of server object.
    * @param params parameters to send create port connection object.
    * @return return value of create port connection method.
    */
    static void* createServerHelper(void* params);
    /**
     * stop server connection.
     */
    virtual void stop() = 0;
    /**
     * destructor, used to free/disallocate memory
     */
    virtual ~Server();
};

#endif
