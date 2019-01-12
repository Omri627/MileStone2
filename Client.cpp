#include <unistd.h>
#include <string.h>
#include "Client.h"
#include "Server.h"
Client::Client(int port, int connectionFd, ClientHandler *clientHandler)  {
    this->port = port;
    this->connectionFd = connectionFd;
    this->handler = clientHandler;
    this->end = 1;
}

Client::Client(int port, ClientHandler *clientHandler) {
    this->port = port;
    this->handler = clientHandler;
    this->end = 1;
}

int Client::getPort() const {
    return port;
}

void Client::setPort(int port) {
    this->port = port;
}

int Client::getConnectionFd() const {
    return connectionFd;
}

void Client::setConnectionFd(int connectionFd) {
    this->connectionFd = connectionFd;
}

ClientHandler *Client::getHandler() const {
    return handler;
}

void Client::setHandler(ClientHandler *handler) {
    this->handler = handler;
}

int Client::getEnd() const {
    return end;
}

void Client::setEnd(int end) {
    this->end = end;
}

Client::~Client() {
    close(this->connectionFd);
}

void Client::send(Server *server, string data) {
    server->sendData(data, this);
}

string Client::readData(Server *server) {
    server->readData(this);
}
