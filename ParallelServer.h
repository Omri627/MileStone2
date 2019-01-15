//
// Created by ranraboh on 12/01/19.
//

#ifndef PARALLEL_SERVER
#define PARALLEL_SERVER

#include "Server.h"
#include <map>
#include <vector>
#include "Client.h"
#include "ThreadPool.h"

class ParallelServer : public Server {
private:
    /* map store for each port, his file descriptor connection */
    map<int, int > serverFd;
    /* bool variable indicate if the first client connect to this server */
    bool firstClient;
    /* thread pool used to manage threads in application */
    ThreadPool* threadPool;
    /* boolean variable indicate whether this server is running or not. */
    bool isRunning;

    /* parameters of listen method. */
    struct listen_params {
        Client* client;
        ParallelServer * server;
    };

    /**
     * getFd method gets a port and returns
     * the file descriptor of connection of this server to this port.
     * @param port port
     * @return returns the file descriptor of connection of this server to given port.
     */
    int getFd(int port);
    /**
     * isConnectedPort method return a boolean variable indicate whether
     * server open connection to given port
     * @param port port
     * @return returns true if server open connection to given port.
     * at any other case returns false
     */
    bool isConnectedPort(int port);
    /**
     * openPortConnection method open a connection to a given port
     * @param port port
     */
    void openPortConnection(int port);
    /**
     * listenToClient method listen to port wait for client connection.
     * @param client client object
     * @return returns indication whether a client connected to server successfully.
     * or error occured
     */
    int listenToClient(Client* client);
    /**
     * static method used to execute listn to client method.
     * @param params gets the parameters for listen to client method
     * @return returns indication whether a client connected to server successfully.
     * or error occured
     */
    static void* listenToClientHelper(void *params);
    /**
     * static method used to execute interact with client method.
     * @param params parameters for interact with client method.
     */
    static void* interactWithClientHelper(void * params);
public:
    /**
    * the cunstructor gets number of parallel threads
    * and creates parallel multi-threading server
    * who is able to handle multiple connected clients request
    * @param threads number of threads
    **/
    ParallelServer(unsigned long threads);
    /**
     * interactWithClient method gets a client
     * interact with client, reads his requests
     * and solve them using client handler object.
     * @param client client object (contains client handler).
     */
    virtual void interactWithClient(Client* client);
    /**
     * open method open a connection in given port.
     * when a client connect in this port to the server,
     * interact with client and solve his input problems.
     * @param port port of connection
     * @param clientHandler aid the server to solve client problems.
     */
    virtual void open(int port, ClientHandler *clientHandler);
    /**
     * stop server connection.
     * close the connection of any linked client.
     */
    virtual void stop();
    /**
     * close the connection between server and given client.
     * @param client client object
     */
    virtual void closeClientConnection(Client* client);
    /**
     * desructor, used to free/disallocate memory
     */
    virtual ~ParallelServer();
};


#endif