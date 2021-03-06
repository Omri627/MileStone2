#include <string.h>
#include "Server.h"
/**
 * createPortConnection method create connection to specific port
 * and returns the file descriptor of this port connection.
 * @param port port number
 * @return returns file descriptor of port connection
 */
int Server::createPortConnection(int port) {
    struct sockaddr_in server_address;       // socket structure
    int socketFd;
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
    return socketFd;
}
/**
* static method which execute create port connection method of server object.
* @param params parameters to send create port connection object.
* @return return value of create port connection method.
*/
void* Server::createServerHelper(void * params) {
    create_params* parameters = (create_params*)params;
    *parameters->socketFd = parameters->server->createPortConnection(parameters->port);
    return nullptr;
}
/**
 * readData method gets a client that connected to server,
 * and reads the data given by this client.
 * @param client client object.
 * @return returns the data received by given client.
 */
string Server::readData(Client* client) {
    //pthread_mutex_lock(&global_mutex);
    const int bufferSize = 512;
    int bytesReaded;
    char * buffer = (char*)calloc(bufferSize,1);
    bzero(buffer,bufferSize);                      // set buffer with null values
    cout << "";
    bytesReaded = read(client->getConnectionFd(), buffer, bufferSize);
    if (bytesReaded < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }
    //pthread_mutex_unlock(&global_mutex);
    buffer[bytesReaded-2] = 0;
    string data = buffer;
    free(buffer);
    return data;
}
/**
 * sendData method gets a message and client which connected to server
 * the method send the client the given message.
 * @param data data/message
 * @param client specific client
 */
void Server::sendData(string data, Client* client) {
    int byteTransmitted;
    /* convert string data into array of characters to transmit */
    const char * charactersData = data.c_str();
    char * msgToTransmit = (char*)calloc(512,1);
    strcpy(msgToTransmit, charactersData);
    msgToTransmit[strlen(msgToTransmit)] = '\r';
    msgToTransmit[strlen(msgToTransmit)] = '\n';
    /* Send message to the server */
    pthread_mutex_lock(&global_mutex);
    byteTransmitted = write(client->getConnectionFd(), msgToTransmit, strlen(msgToTransmit));
    pthread_mutex_unlock(&global_mutex);
    if (byteTransmitted < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
    free(msgToTransmit);
}
/**
* destructor, used to free/disallocate memory
*/
Server::~Server() {
    pthread_mutex_destroy(&global_mutex);
}
