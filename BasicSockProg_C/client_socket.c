// Made by Tofufu

/*
To Run:
 Compile both client & server .c files seperately
 Open up 2 command prompts
 ./server prog (so that it can start listening for connections)
 ./client (so that it can try to connect)
 Done!
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> // Socket API (Contains MACROs, types, etc.)
#include <unistd.h> // Contains close()
// defines sockaddr_in struct (Used to store addresses of IP family)
// sockaddr_in has to be casted to (struct sockaddr) to use in socket inerface
#include <netinet/in.h>
#include <sys/types.h> // for recv() size_t

int main()
{
    /*
     Client Socket Workflow:
     Create --> Connect --> Send/Receive --> Close
     */
    
    /*
     Creating Client Socket (sys/socket.h):
     int socket(int namespace, int style, int protocol)
        namespace = 'Domain of Socket' | Protocol Family
            int PF_INET = IPv4 namespace and its family of protocols    [macro-socket.h]
            int PF_LOCAL = Local Namespace                              [macro-socket.h]
            int AF_INET = IPv4 addresses                                [macro-socket.h]
            AF_INET (address family) v PF_INET (protocol family):
                -Use AF_INET in struct sockaddr_in and PF_INET in socket() call
        style = Communication Style | Type of socket
            int SOCK_STREAM = reliable data trans. stream of bytes (TCP)        [macro-socket.h]
            int SOCK_DGRAM = unreliable individually-addressed packets (UDP)    [macro-socket.h]
                -Each data to socket becomes 1 packet (needs recipient address for each packet
        protocol = Protocol for communication (send/receiv data)
            Default Protocol (0) - Comes with each combo namespace/style (udp or tcp)
            Protocol specification used mainly with raw sockets that are indp of protocols
     Returns:
        File Descriptor for new socket (# that supports r/w operations) or -1 for error
     */
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    /*
     Specifying Server Address to Connect to (netinet/in.h):    [used in connect()]
     sockaddr_in - Used to store addresses for IP family
     struct sockaddr_in
     {
        sa_family_t sin_family  (unsigned int-socket.h): AF_INET    [Address Family]
        in_port_t sin_port      (uint16): htons(port#)              [Port we want to connect to]
                                16 short - htons():
                                converts hostByteOrder (byte order on machine) -> networkByteOrder(big edian)
        struct in_addr sin_addr |struct in_addr { long s_addr; }    [IP Address to connect to]
                                INADDR_ANY = All available interfaces - Connecting to our own local address
                                             eqv to 0.0.0.0 in IPv4 ~ All IPv4 Addresses in machine
        unsigned char sin_zero[8]   [Padding - should be all zeros]
     }
     */
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9000);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    /*
     Connecting to Server (sys/socket.h):
     int connect(int socket, const struct sockaddr* address, socklen_t address length)
        socket = clientSocket file descriptor
        address = Server address we're connecting to
                sockaddr = generic descriptor for any type of socket operation (ex: sockaddr_un for Unix socks)
                sockaddr_in = struct for IP communication
                ^ Have to cast
        length = length of server's address
     Returns:
        0 = connection successful | -1 = error
     */
    int connectionSuccess = connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (connectionSuccess == -1) // if failed connection
    {
        printf("Connection Error\n");
    } // if(connectionSuccess)
    
    /*
     Receiving Data From Server (sys/socket.h) & (sys/types.h):
     ssize_t recv(int receivingSocketDescriptor, void* buffer, size_t length_buffer, int flags);
        size_t & ssize_t declared in types.h
        buffer = Holds the data received by Server
        length_buffer = size of the data [Use sizeof()]
        optional flags formed by OR-ing: MSG_DONTWAIT, MSG_ERRQUEUE, etc. (See Manual for flags)
            flags: 0 = none
     Returns:
        Success = length of msg in bytes | no msg avail ~ server shutdown = 0 | error = -1
     */
    char serverDataReceived[100];
    recv(clientSocket, &serverDataReceived, sizeof(serverDataReceived), 0);
    printf("Received Data: %s", serverDataReceived);
    
    /*
     Close Connection/Socket (unistd.h):
     int close(clientSocket) - Closing the file descriptor
     Returns:
        0 success, -1 failure
     */
    close(clientSocket);
    return 0;
}
