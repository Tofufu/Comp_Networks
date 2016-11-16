/*
 To Run:
 -Run the Server First so that it can always listen for connection
 -Then Run the Client program so that it can ask for connection
 
 Manual Pages:
 man function
 ... 
 man socket
 */
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <unistd.h>

// Server Socket: Create()-->Bind() socket to an IP/Port-->Listen() for connection at the IP/Port-->Accept() connection and rec/send data
int main()
{
    char server_message[256] = "Hello Hello Hello!\n"; // String that will be sent off to client
    
    // Creating Server Socket
    int server_socket; // holds return value of socket calls
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Defining Server Address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;
    
    // Binding socket binding to IP/Port
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)); // socket, address-casted, size of server address
    
    // Listening for connections at the port
    listen(server_socket, 2); // server socket, backlog - how many connections can be waiting for this socket.. right now can be 1 because we know we're only doing 1 connection right now - doesn't matter
    
    // Integer to hold the client socket, once we're able to listen to connections we can start accepting connections
    int client_socket;
    
    //Accepting connections - accept() returns the client socket #
    client_socket = accept(server_socket, NULL, NULL); // socket we're accepting connections on aka server socket, structures that contain the address of the client connection and size of client's address (setting in null because we're using local machine - We can now send data to client socket
    
    // Sending/Receiving Data
    send(client_socket, server_message, sizeof(server_message), 0); // socket we're sending to, data we're sending, size of the message, optional flags
    
    // Close socket after sending data
    close(server_socket);
    return 0;
}
