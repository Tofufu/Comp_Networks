// Made by Tofufu
// SEE client_socket.c for more indepth comments!! <( ^ _ ^ )>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>

int main()
{
    /*
     Server Socket Workflow:
     Create --> Bind --> Listen --> Accept --> Send/Receive --> Close
     */
    
    // Creating Server Socket (File Descriptor)
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Defining Server's Adddress
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9000);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    /*
     Binding Server's Socket -> IPAdd/Port so Server can listen for connections (sys/socket.h):
     int bind( int socket, const struct sockaddr* address, socklen_t addresslen)
        socket = Server's socket File Descriptor
        address = Socket Address assigned to socket ^ [cast sockaddr_in]
        addresslen = length of socket address [sizeof()]
     Returns:
        0 = success, -1 = error
     */
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    
    /*
     Constantly Listening for connections (sys/socket.h):
     int listen(int socket, int backlog)
        socket = Server's socket File Descriptor using to listen
        backlog = max # of connections in socket's listen queue
                set to 1 b/c we know only 1 connection w/ client.c
     Returns:
        0 = success, -1 = error
     */
    listen(serverSocket, 2);
    
    /*
     Accepting Connection (sys/socket.h):
     int accept( int socket, struct sockaddr* address, socklen_t *address_len)
     Takes connection from queue, Creates new socket same as socket specified, creates FD for new socket
        socket = Accepting Connections Server Socket File Descriptor
        address = NULL (local listening to all) | ptr to struc sockaddr (address) of client socket
        address_len = NULL (local) | length of the client's address
     Returns:
        File Descriptor of client socket of accepted connection | -1 = error
     */
    int clientSocket = accept(serverSocket, NULL, NULL);
    
    /*
     Sending Data (sys/socket.h) & (sys/types.h):
     ssize_t send(int clientSocket, const void* dataSending, size_t dataSendingLength, int flags)
     Return:
        Success = # of bytes sent | -1 = error
     */
    char dataSending[100] = "Tofufu!\n";
    send(clientSocket, dataSending, sizeof(dataSending), 0);
    
    /*
     Closing Server Socket/Connection
     */
    close(serverSocket);
    return 0;
}
