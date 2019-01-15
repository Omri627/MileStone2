#include <string.h>
#include "ParallelServer.h"
#include "SerialServer.h"
/**
 * cunstructor gets number of parallel threads
 * and creates parallel multi-threading server
 * who is able to handle multiple connected clients request
 * @param threads number of threads
 **/
ParallelServer::ParallelServer(unsigned long threads) {
    this->firstClient = true;
    this->threadPool = new ThreadPool(threads);
    this->isRunning = true;
}
/**
 * getFd method gets a port and returns
 * the file descriptor of connection of this server to this port.
 * @param port port
 * @return returns the file descriptor of connection of this server to given port.
 */
int ParallelServer::getFd(int port) {
    return this->serverFd[port];
}
/**
 * isConnectedPort method return a boolean variable indicate whether
 * server open connection to given port
 * @param port port
 * @return returns true if server open connection to given port.
 * at any other case returns false
 */
bool ParallelServer::isConnectedPort(int port) {
    map<int, int >::iterator iterator;
    iterator = this->serverFd.find(port);
    if (iterator != this->serverFd.end())
        return true;
    return false;
}
/**
 * openPortConnection method open a connection to a given port
 * @param port port
 */
void ParallelServer::openPortConnection(int port) {
    ThreadPool::task task;
    /* create thread to create server with given port */
    if (this->isConnectedPort(port))
        return;
    create_params createParams;                         // parameters for create server
    /* set parameters for create  */
    createParams.port = port;
    createParams.server = this;
    createParams.socketFd = new int;
    /* create server in seperate thread */
    task.operation = &Server::createServerHelper;
    task.params = &createParams;
    task.type = ThreadPool::JOIN;
    this->threadPool->enqueueTask(task);
    this->serverFd[port] = *createParams.socketFd;
    free(createParams.socketFd);
}
/**
 * listenToClient method listen to port wait for client connection.
 * @param client client object
 * @return returns indication whether a client connected to server successfully.
 * or error occured
 */
int ParallelServer::listenToClient(Client* client) {
    struct sockaddr_in client_address;
    int connectionFd;
    int serverFd = this->getFd(client->getPort());
    int clientSizeStructure;
    // start listening for the clients,
    // the process be in sleep mode and will wait for the incoming connection
    listen(serverFd, SOMAXCONN);
    if (serverFd == -1 || !this->isRunning) {
        cout << "connection lost" << endl;
        return 0;
    }
    //* Accept actual connection from the client *//*
    clientSizeStructure = sizeof(client_address);
    connectionFd = accept(serverFd, (struct sockaddr *) &client_address, (socklen_t *) &clientSizeStructure);
    if (connectionFd < 0) {
        return 0;
        //perror("ERROR on accept");
        //exit(1);
    }
    if (this->isRunning) {
        client->setConnectionFd(connectionFd);
        cout << "request accepted" << endl;
    } else {
        close(connectionFd);
        cout << "request rejected" << endl;
    }
}
/**
 * open method open a connection in given port.
 * when a client connect in this port to the server,
 * interact with client and solve his input problems.
 * @param port port of connection
 * @param clientHandler aid the server to solve client problems.
 */
void ParallelServer::open(int port, ClientHandler *clientHandler) {
    ThreadPool::task listenTask, interactTask;
    listen_params listenParams, interactParams;

    /* create connection of server in given port */
    this->openPortConnection(port);
    /* listen and connect to client */
    /* connect and handle client */
    /* create thread to listen for possible clients requests */
    Client* client = new Client(port, clientHandler);
    client->setConnectionFd(-1);
    listenParams.client = client;
    listenParams.server = this;
    listenTask.params = &listenParams;
    listenTask.type = (firstClient)?ThreadPool::JOIN:ThreadPool::TIMEOUT;
    listenTask.operation = &ParallelServer::listenToClientHelper;
    this->threadPool->enqueueTask(listenTask);
    sleep(1);
    /* close if timer is over */
    if (client->getConnectionFd() == -1) {
        cout << "time elapsed for connection" << endl;
        this->stop();
        delete clientHandler;
        return;
    }
    /* connect and handle client */
    interactParams.client = client;
    interactParams.server = this;
    interactTask.params = &listenParams;
    interactTask.type = ThreadPool::DETACH;
    interactTask.operation = &ParallelServer::interactWithClientHelper;
    this->threadPool->enqueueTask(interactTask);
    this->firstClient = false;
    /* keep listen to port */
    this->open(port, clientHandler);
}
/**
 * stop server connection.
 * close the connection of any linked client.
 */
void ParallelServer::stop() {
    this->isRunning = false;
    threadPool->waitForActivatedTasks();
    for (pair<int, int> portFd : this->serverFd)
        close(portFd.second);
}
/**
 * close the connection between server and given client.
 * @param client client object
 */
void ParallelServer::closeClientConnection(Client* client) {
    delete client;
    this->threadPool->taskFinish(pthread_self());
}
void* ParallelServer::listenToClientHelper(void *params) {
    listen_params* listenParams = (listen_params*)params;
    listenParams->server->listenToClient(listenParams->client);
    return nullptr;
}
/**
 * interactWithClient method gets a client
 * interact with client, reads his requests
 * and solve them using client handler object.
 * @param client client object (contains client handler).
 */
void ParallelServer::interactWithClient(Client* client) {
    /* handle client request */
    try {
        client->getHandler()->handleClient(this,client);
    } catch (const char* error) {
        this->sendData(error, client);
    }
    /* close connection with client */
    this->closeClientConnection(client);
}
/**
 * static method used to execute interact with client method.
 * @param params parameters for interact with client method.
 */
void* ParallelServer::interactWithClientHelper(void *params) {
    listen_params* parameters = (listen_params*)params;
    parameters->server->interactWithClient(parameters->client);
    return nullptr;
}
ParallelServer::~ParallelServer() {
    delete this->threadPool;
    this->serverFd.clear();
}
