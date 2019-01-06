#ifndef CLIENT_HANDLER
    #define CLIENT_HANDLER

#include <iostream>
using namespace std;
class ClientHandler {
    virtual void handleClient(istream input, ostream output) = 0;
};


#endif //PROJECT2_CLIENTHANDLER_H
