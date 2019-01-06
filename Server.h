#ifndef PROJECT2_SERVER_H
    #define PROJECT2_SERVER_H

#include "ClientHandler.h"

class Server {
    virtual void open(int port ,ClientHandler clientHandler) = 0;
    virtual void stop() = 0;
};


#endif
