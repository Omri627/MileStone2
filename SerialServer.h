#ifndef PROJECT2_SERIALSERVER_H
#define PROJECT2_SERIALSERVER_H

#include "Server.h"
class SerialServer : public Server {
private:
    string address;
public:
    SerialServer(string address);

    SerialServer();
};


#endif //PROJECT2_SERIALSERVER_H
