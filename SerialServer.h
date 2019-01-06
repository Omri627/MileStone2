#ifndef PROJECT2_SERIALSERVER_H
#define PROJECT2_SERIALSERVER_H

#include "Server.h"
class SerialServer : public server_side::Server {
private:
    bool isRunning;
    string address;

    int createServer(int port);

    void listenToClient(int socketFd);
public:
    SerialServer(string address);

    SerialServer();

    void open(int port, ClientHandler clientHandler) override;

    void stop() override;

};


#endif //PROJECT2_SERIALSERVER_H
