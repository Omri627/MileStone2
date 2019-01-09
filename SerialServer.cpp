#include <string.h>
#include <fstream>
#include <bits/signum.h>
#include "SerialServer.h"
#include <signal.h>
SerialServer::SerialServer(string address) {
    this->address = address;
}

SerialServer::SerialServer() {

}

int SerialServer::createServer(int port) {
    struct sockaddr_in server_address;       // socket structure

    // AF-INET = address family ipv4
    // SOCK_STREAM = protocol tcp provides reliable, ordered, and error-checked delivery of bytes.
    // protocol = 0  default protocol for the given combination of family and type
    // socket method opens socket by insert socket resource into resources table of operating system
    // and returns integer which uniquely identifies a resouce in operating system.
    this->socketFd = socket(AF_INET, SOCK_STREAM, 0);

    // send message in case there is an error in opening socket
    if (socketFd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    //* Initialize socket structure *//
    bzero((char *) &server_address, sizeof(server_address));  // used to set all the socket structures with null values.
    server_address.sin_family = AF_INET;                      // setting address family (=ipv4)
    server_address.sin_addr.s_addr = INADDR_ANY;              // internal ip address
    server_address.sin_port = htons(port);              // setting server port

    //* bind function assigns a local protocol address to a socket. *//*
    if (bind(socketFd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    cout << "server opened listen for client request" << endl;
}

int SerialServer::listenToClient() {
    struct sockaddr_in client_address;
    int clientSizeStructure;
    // start listening for the clients,
    // the process be in sleep mode and will wait for the incoming connection
    listen(socketFd, 5);
    if (this->socketFd == -1) {
        cout << "connection lost" << endl;
        return 0;
    }
    //* Accept actual connection from the client *//*
    clientSizeStructure = sizeof(client_address);
    this->clientFd = accept(socketFd, (struct sockaddr *) &client_address, (socklen_t *) &clientSizeStructure);
    if (this->clientFd < 0) {
        return 0;
        //perror("ERROR on accept");
        //exit(1);
    }
    cout << "request accepted"  << endl;
}

void SerialServer::open(int port, ClientHandler* clientHandler) {
    string problem;                               // problem that has been received from client
    pthread_t createThread, listenThread;         // thread for create server with port
    create_params createParams;                   // parameters for create method
    struct timespec abstime;                      // timer object
    createParams.server = this;
    createParams.port = port;
    /* create thread to create server with given port */
    pthread_create(&createThread, nullptr, &SerialServer::createServerHelper, &createParams);
    pthread_join(createThread, nullptr);
    /* connect and handle each client */
    while (true) {
        /* set timer for listen thread */
        clock_gettime(CLOCK_REALTIME, &abstime);
        abstime.tv_sec += 10;
        /* create thread to listen for possible clients requests */
        pthread_create(&listenThread, nullptr, &SerialServer::listenToClientHelper, this);
        pthread_timedjoin_np(listenThread, nullptr, &abstime);
        if (this->clientFd <= 0) {
            cout << "time elapsed" << endl;
            break;
        }
        /* break if timout is over */
        problem = this->readData();
        clientHandler->handleClient(problem, this);
        this->closeClientConnection();
    }
    delete(clientHandler);
    this->stop();
}
void* SerialServer::createServerHelper(void * params) {
    create_params* parameters = (create_params*)params;
    parameters->server->createServer(parameters->port);
    return nullptr;
}

void* SerialServer::listenToClientHelper(void *params) {
    ((SerialServer *) params)->listenToClient();
}
void SerialServer::stop() {
    this->isRunning = false;
    /* reset file descriptors */
    this->socketFd = -1;
    this->clientFd = -1;
}
void SerialServer::closeClientConnection() {
    close(this->clientFd);
    this->clientFd = -1;
}