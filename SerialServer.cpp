#include <string.h>
#include <fstream>
#include <bits/signum.h>
#include "SerialServer.h"
#include <signal.h>

SerialServer::SerialServer() {

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
        client->setEnd(1);
        while (client->getEnd()) {
            try {
                client->setEnd(clientHandler->handleClient(this, client));
            } catch (const char* error) {
                this->sendData(error, client);
            }
        }
        /* close connection with client */
        this->closeClientConnection();
    }
    delete(clientHandler);
    this->stop();
}
/*void* SerialServer::createServerHelper(void * params) {
    create_params* parameters = (create_params*)params;
    parameters->server->createPortConnection(parameters->port);
    return nullptr;
}*/

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
