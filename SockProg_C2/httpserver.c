//HTTP req - we have to specify what type of data we want
// Sockets working with HTTP protocol
/*
 This is just a simple HTTP server that sends data - doesn't deal with other requests besides "get" - not a full implmentation of HTTP protocol - just responds with the HTTP header and HTTP status codes...
 Only thing different is that now we're sending data!
 Can open web browser and test!
 
 Running Server / Accessing via browser:
 -run server
 -go to localhost:port# on browser at the same time
 localhost - local ip bounded to the ip - interface we can access and navigate to port number
 -shows us what's going to be served at that port number
 */
#include <stdio.h>
/*
 -HTTP Client: sends req to ask for resource (GET /index.html) -> Server
 -HTTP Server: responds w/ the resource (in response body) and status code (200 OK!) or why it couldn't be return -> Client
 */

/*
 HTTP server that will render HTML for us
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>// used to manipulate string data (http response from server)

int main()
{
    // rendering html file (want to send file as http response) - opening file to serve
    FILE* htmlData; // file pointer to hold the data
    // html file is the response/data we're going to send to client
    htmlData = fopen("index.html", "r"); // file opening, what we're going to do with the file
    char responseData[1024]; // string to store the stuff inside the file
    fgets(responseData, 1024, htmlData); // reading file into the string (where to read to, how much to read, file reading from)
    
    
    // First line of response - has status code (says what happens when resource given) - response header
    // lets client know that it's okay and the stuff will be in the response body
    // include string header we want to combine response body + header (strcat) will concatinate the hdr + data
    char httpHeader[2048] = "HTTP/1.1 200 OK\r\n\n"; //httpversion#, status code , rest will be the data
    strcat(httpHeader, responseData); // combining them

    
    // Creating server socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    // server address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY; // any address that is avaliable
    //binding to any port
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    //listening at port
    listen(serverSocket, 5);
    
    // client socket
    int clientSocket;
    //Wrap in infinite while loop - we want server to continuously server and keep responding to any requests
    while(1)
    {
        // accept connection with client socket - not storing address so nulls
        clientSocket = accept(serverSocket, NULL, NULL);
        // sending data to client - httpheader has combo of header and response body
        send(clientSocket, httpHeader, sizeof(httpHeader), 0);
        // close client
        close(clientSocket);
    }
    return 0;
}
