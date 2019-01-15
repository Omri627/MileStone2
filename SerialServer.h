#ifndef PROJECT2_SERIALSERVER_H
    #define PROJECT2_SERIALSERVER_H

#include <iostream>
#include "Server.h"
#include <time.h>

class SerialServer : public Server {
private:
    /* indicate whether the server is running or not */
    bool isRunning;
    /* connect socket file descriptor */
    int socketFd;
    /* client connection file descriptor */
    int clientFd;
    /* create method parameters */

    /**
     * listenToClient method listen for client in given port.
     * @return returns the socket file descriptor of this connection
     */
    int listenToClient();
    /**
     * listenToClientHelper is static method which execute listenToClient method of server.
     * @param params parameters of the listen to client method
     * @return returns the socket file descriptor of this connection
     */
    static void* listenToClientHelper(void* params);
    /**
     * close the connection between server and client.
     */
    void closeClientConnection();

public:
    /**
     * creates a local serial server object.
     * which has the ability to open connection with clients and handle their requests.
     */
    SerialServer();
    /**
     * open method open a connection between client and server.
     * the method reads client requests and solves his problems using client handler object.
     * @param port port of the connection
     * @param clientHandler  aid the server to solve client problems.
     */
    virtual void open(int port, ClientHandler* clientHandler);
    /**
     * stop server action. if any client connect to the server at that moment,
     * close the connection.
     */
    virtual void stop();

};


#endif