#include <unistd.h>
#include <string.h>
#include "Client.h"
#include "Server.h"
/**
 * create new Client object initiallized with port, connection file descriptor and
 * client handler object
 * @param port port that this client connected to server
 * @param connectionFd file descriptor of the connection between client and server
 * @param clientHandler client handler object used to aid sever to solve client requests
 */
Client::Client(int port, int connectionFd, ClientHandler *clientHandler)  {
    this->port = port;
    this->connectionFd = connectionFd;
    this->handler = clientHandler;
    this->end = 1;
}
/**
 * create new Client object initiallized with port, connection file descriptor and
 * client handler object
 * @param port port that this client connected to server
 * @param clientHandler client handler object used to aid sever to solve client requests
 */
Client::Client(int port, ClientHandler *clientHandler) {
    this->port = port;
    this->handler = clientHandler;
    this->end = 1;
}
/**
 * getter method of port field
 * @return returns the port of the connection between server and this client
 */
int Client::getPort() const {
    return port;
}
/**
 * setter method of port field.
 * used to set the port of the connection between server and client
 * @param port port that this client connected to server
 */
void Client::setPort(int port) {
    this->port = port;
}
/**
 * getter method of connection file descriptor field
 * @return returns the file descriptor of the connection between client and server.
 */
int Client::getConnectionFd() const {
    return connectionFd;
}
/**
  * setter method of connection file descriptor field.
  * used to sets the value of file descriptor of server with client
  * @param connectionFd file descriptor of the connection between client and server
  */
void Client::setConnectionFd(int connectionFd) {
    this->connectionFd = connectionFd;
}
/**
 * getter method of handler field
 * @return return the client handler object.
 */
ClientHandler *Client::getHandler() const {
    return handler;
}
/**
 * setter method of client handler field
 * used to sets the client handler object that can solve client rquests/
 * @param handler client handler object
 */
void Client::setHandler(ClientHandler *handler) {
    this->handler = handler;
}
/**
 * getter method of end field
 * @return returns end field of client.
 * indicate whether the client finished his requests.
 */
int Client::getEnd() const {
    return end;
}
/**
 * setter method of end field
 * used to set the value of end
 * @param end indicate whether the connection ends
 */
void Client::setEnd(int end) {
    this->end = end;
}
/**
  * descructor, used to free, disallocate memory
  */
Client::~Client() {
    close(this->connectionFd);
}
/**
 * send message or data from this client to server
 * @param server connected server object
 * @param data data/message for sending
 */
void Client::send(Server *server, string data) {
    server->sendData(data, this);
}
/**
 * readData reads data sent by the server to this client
 * @param server server object
 * @return returns the data sent by the server.
 */
string Client::readData(Server *server) {
    server->readData(this);
}
