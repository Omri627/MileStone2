#ifndef PARALLEL_SERVER
    #define PARALLEL_SERVER

#include "Server.h"
#include <list>
#include <map>
class ParallelServer : public Server {
private:
    bool isRunning;

    map< int, int > portsFd;

    bool isServerListenPort(int port);

    bool getConnectionSocketFd(int port);
public:
    virtual void open(int port, ClientHandler *clientHandler);

    virtual string readData();

    virtual void sendData(string data);

    virtual void stop();
};


#endif //PROJECT2_PARALLELSERVER_H
