#ifndef PROJECT2_SERVER_H
    #define PROJECT2_SERVER_H

#include "ClientHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
namespace  server_side {
    class Server {
    public:
        virtual void open(int port, ClientHandler clientHandler) = 0;

        virtual void stop() = 0;
    };
}



#endif
