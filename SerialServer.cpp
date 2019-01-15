#include <string.h>
#include <fstream>
#include <bits/signum.h>
#include "SerialServer.h"
#include <signal.h>

/**
 * creates a local serial server object.
 * which has the ability to open connection with clients and handle their requests.
 */
SerialServer::SerialServer() {

}
/**
 * listenToClient method listen for client in given port.
 * @return returns the socket file descriptor of this connection
 */
int SerialServer::listenToClient() {
    struct sockaddr_in client_address;
    int clientSizeStructure;
    // start listening for the clients,
    // the process be in sleep mode and will wait for the incoming connection
    listen(socketFd, SOMAXCONN);
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
/**
 * open method open a connection between client and server.
 * the method reads client requests and solves his problems using client handler object.
 * @param port port of the connection
 * @param clientHandler  aid the server to solve client problems.
 */
void SerialServer::open(int port, ClientHandler* clientHandler) {
    pthread_t createThread, listenThread;         // thread for create server with port
    create_params createParams;                   // parameters for create method
    struct timespec abstime;                      // timer object
    Client* client = new Client(port, clientHandler);
    createParams.server = this;
    createParams.port = port;
    createParams.socketFd = &this->socketFd;

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

        /* close if timer is over */
        if (this->clientFd <= 0) {
            cout << "time elapsed" << endl;
            break;
        }
        /* handle all client requests */
        client->setConnectionFd(this->clientFd);
        try {
            client->setEnd(clientHandler->handleClient(this, client));
        } catch (const char* error) {
            this->sendData(error, client);
        }
        /*client->setEnd(1);
        while (client->getEnd()) {
            try {
                client->setEnd(clientHandler->handleClient(this, client));
            } catch (const char* error) {
                this->sendData(error, client);
            }
        } */
        /* close connection with client */
        this->closeClientConnection();
    }
    delete(clientHandler);
    this->stop();
}
/**
 * listenToClientHelper is static method which execute listenToClient method of server.
 * @param params parameters of the listen to client method
 * @return returns the socket file descriptor of this connection
 */
void* SerialServer::listenToClientHelper(void *params) {
    ((SerialServer *) params)->listenToClient();
}
/**
 * stop server action. if any client connect to the server at that moment,
 * close the connection.
 */
void SerialServer::stop() {
    this->isRunning = false;
    /* reset file descriptors */
    this->socketFd = -1;
    this->clientFd = -1;
}
/**
  * close the connection between server and client.
  */
void SerialServer::closeClientConnection() {
    close(this->clientFd);
    this->clientFd = -1;
}
