#include <stdio.h>
#include <stdlib.h>


#include <sys/types.h> // def for socket funcs
#include <sys/socket.h> // contains the API for sockets

// structures for storing address information
#include <netinet/in.h>

#include <unistd.h> // close() defined here

int main()
{
    // Client Socket: Create-->Connect-->Send/Receive-->Close
    // Creating a Socket
    int network_socket; // int to hold socket descriptor (the info about socket)
    network_socket = socket(AF_INET, SOCK_STREAM, 0); // Domain of socket - AF_INET = internet socket | Type of socket - sock stream:TCP socket vs datagram socket:UDP | Protocol being used: 0 = default. Sometimes want to specify protocol specifically like raw sockets that are independent of protocol
    
    // Specifying address to connect to - inet has structure that contains fields that allows us to know address and port of the remote socket we're connecting to
    struct sockaddr_in server_address; // defining structure
    server_address.sin_family = AF_INET; // specifying address family, same as family as socket (type of address)
    server_address.sin_port = htons(9002);// port we're going to connect to - could pass in as int but data format diff from structure - need conversion function that puts in integer port # into correct network byte ordering - port number that isn't being used by anything
    server_address.sin_addr.s_addr = INADDR_ANY; // actual address we're connecting to - the ip address - (sin_addr = structure) - connecting to our own local address - inddr = 0.0.0.0 - moves to any ip address on local machine
    
    // Connecting
    int connection_status = connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address)); // socket, serv_addr structure casted as ptr, size of address - returns an integer lets us know if connection was successful or not
    // connect() returns: 0 = okay, -1 = not able to connect
    if ( connection_status == -1)
    {
        printf("There was an error with connection\n");
    }
    
    // Sending or Receiving Data (This case receiving data from server)
    char server_response[256]; // string to hold data received
    recv(network_socket, &server_response, sizeof(server_response), 0); // socket, string to hold data, size of data - just using size of the buffer for this, optional flag parameter - left 0
    
    // Print out data received
    printf("The server sent data: %s", server_response);
    
    // Close connection / socket
    close(network_socket); // takes in the socket
    
    
    
    return 0;
}
