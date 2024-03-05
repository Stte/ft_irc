#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#define MYPORT "4444"

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM,  0);
    if (sockfd <  0) {
        std::cerr << "ERROR opening socket" << std::endl;
        return -1;
    }

    // Set up the server address structure
    memset(&serv_addr,  0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(MYPORT)); // Convert the port number to network byte order
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with the server's IP address if not localhost

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) <  0) {
        std::cerr << "ERROR connecting" << std::endl;
        close(sockfd);
        return -1;
    }

    std::cout << "Connected to the server!" << std::endl;

    // Close the socket
    close(sockfd);

    return  0;
}
