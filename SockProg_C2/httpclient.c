/*
 To Run:
 Get IP address of a website (ping google)
 ./httpclient (ip address)
 */
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h> // contains function for converting ip address

// client requesting data from server
// command line specifies which server we're going to connect to
int main(int argc, char* argv[]) // command line arguments we past in
{
    char *serverAddress;
    serverAddress = argv[1]; // server's address argv[0] = ./program that we're going to connect to
    
    //creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    //client is going to connect to this address
    struct sockaddr_in remoteAddress;
    remoteAddress.sin_family = AF_INET;
    remoteAddress.sin_port = htons(80); // port that http uses
    
    //arpa/inet.h function
    // converts string address to format for address structure so we can connect to it
    // string address passed in via command line
    inet_aton(serverAddress, &remoteAddress.sin_addr.s_addr);//serveraddress to connect to, where to store the converted address (ptr/ref) to place where we were storing addresses before - previously was putting INETA but now we're doing a specifically stating
    
    // asking to connect to server
    connect(clientSocket, (struct sockaddr*)&remoteAddress, sizeof(remoteAddress));
    
    // holding request and response
    char request[] = "GET / HTTP/1.1\r\n\r\n"; // the http request: Method (what we want to do), what resource we want (/ = saying we want the root location on the server - requesting a website without a particular page), version of protocol we're using, \r\n\r\n = means we're finishing up request
    char response[4096];
    
    // sending HTTP request
    send(clientSocket, request, sizeof(request), 0); // socket, what we're sending
    
    // receive the response from the server
    recv(clientSocket, &response, sizeof(response), 0); // clientsocket, where we want to store response
    
    // print out what we received from the server
    printf("Reponse: %s\n", response);
    close(clientSocket);
    return 0;
}
