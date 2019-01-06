#include <string.h>
#include "SerialServer.h"
SerialServer::SerialServer(string address) {
    this->address = address;
}

SerialServer::SerialServer() {

}

int SerialServer::createServer(int port) {
    int socketFd;                            // socket file descriptor
    struct sockaddr_in server_address;       // socket structure

    // AF-INET = address family ipv4
    // SOCK_STREAM = protocol tcp provides reliable, ordered, and error-checked delivery of bytes.
    // protocol = 0  default protocol for the given combination of family and type
    // socket method opens socket by insert socket resource into resources table of operating system
    // and returns integer which uniquely identifies a resouce in operating system.
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    // send message in case there is an error in opening socket
    if (socketFd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    //* Initialize socket structure *//*
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
    return socketFd;
}

void SerialServer::listenToClient(int socketFd) {
    struct sockaddr_in client_address;
    int clientSizeStructure, connectFd;
    // start listening for the clients,
    // the process be in sleep mode and will wait for the incoming connection
    listen(socketFd, 5);
    //* Accept actual connection from the client *//*
    clientSizeStructure = sizeof(client_address);
    connectFd = accept(socketFd, (struct sockaddr *) &client_address, (socklen_t *) &clientSizeStructure);
    if (connectFd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    cout << "request accepted"  << endl;

}

void SerialServer::open(int port, ClientHandler clientHandler) {

}

void SerialServer::stop() {

}
