#ifndef PROJECT2_CLIENT_H
#define PROJECT2_CLIENT_H

#include "ClientHandler.h"
class Client {
private:
    /* port that this client connected to server */
    int port;
    /* file descriptor of the connection between client and server */
    int connectionFd;
    /* client handler object used to aid sever to solve client requests */
    ClientHandler *handler;
    /* indicate whether the connection ends */
    int end;
public:
    /**
     * create new Client object initiallized with port, connection file descriptor and
     * client handler object
     * @param port port that this client connected to server
     * @param connectionFd file descriptor of the connection between client and server
     * @param clientHandler client handler object used to aid sever to solve client requests
     */
    Client(int port, int connectionFd, ClientHandler *clientHandler);
    /**
     * create new Client object initiallized with port, connection file descriptor and
     * client handler object
     * @param port port that this client connected to server
     * @param clientHandler client handler object used to aid sever to solve client requests
     */
    Client(int port, ClientHandler *clientHandler);
    /**
     * getter method of port field
     * @return returns the port of the connection between server and this client
     */
    int getPort() const;
    /**
     * setter method of port field.
     * used to set the port of the connection between server and client
     * @param port port that this client connected to server
     */
    void setPort(int port);
    /**
     * getter method of connection file descriptor field
     * @return returns the file descriptor of the connection between client and server.
     */
    int getConnectionFd() const;
    /**
     * setter method of connection file descriptor field.
     * used to sets the value of file descriptor of server with client
     * @param connectionFd file descriptor of the connection between client and server
     */
    void setConnectionFd(int connectionFd);
    /**
     * getter method of handler field
     * @return return the client handler object.
     */
    ClientHandler *getHandler() const;
    /**
     * setter method of client handler field
     * used to sets the client handler object that can solve client rquests/
     * @param handler client handler object
     */
    void setHandler(ClientHandler *handler);
    /**
     * getter method of end field
     * @return returns end field of client.
     * indicate whether the client finished his requests.
     */
    int getEnd() const;
    /**
     * setter method of end field
     * used to set the value of end
     * @param end indicate whether the connection ends
     */
    void setEnd(int end);
    /**
     * send message or data from this client to server
     * @param server connected server object
     * @param data data/message for sending
     */
    void send(Server *server, string data);
    /**
     * readData reads data sent by the server to this client
     * @param server server object
     * @return returns the data sent by the server.
     */
    string readData(Server *server);
    /**
     * descructor, used to free, disallocate memory
     */
    virtual ~Client();
};

#endif