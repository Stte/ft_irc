#include "stdio.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

#define MYPORT "3490"  // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue will hold


// struct addrinfo

/*struct addrinfo {
    int              ai_flags;     // AI_PASSIVE, AI_CANONNAME, etc.
    int              ai_family;    // AF_INET, AF_INET6, AF_UNSPEC
    int              ai_socktype;  // SOCK_STREAM, SOCK_DGRAM
    int              ai_protocol;  // use 0 for "any"
    size_t           ai_addrlen;   // size of ai_addr in bytes
    struct sockaddr *ai_addr;      // struct sockaddr_in or _in6
    char            *ai_canonname; // full canonical hostname

    struct addrinfo *ai_next;      // linked list, next node
};*/

int main()
{
    struct sockaddr_storage their_addr; // incoming connections info saved here from accept()
    socklen_t addr_size; // to keep their_addr size
    struct addrinfo hints, *res; // look up i printed the struct for your understanding
    int status, sockfd, new_fd; // sock fd, new fd after there is a connection


    // first, load up address structs with getaddrinfo():

    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;  // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;  // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    // get ready to connect
    // res now points to a linked list of 1 or more struct addrinfos
    if ((status = getaddrinfo(NULL, MYPORT, &hints, &res)) != 0)
    {
    	printf("Error in getaddrinfo: %s", gai_strerror(status));
		return (-1);
    }

    // make a socket
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd == -1)
    {
    	printf("error is socket %s %d", strerror(errno), errno);
		return (-1);
    }
	printf("Socket created\n");
    // bind the socket
    if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1)
    {
    	printf("Error in bind: %s", strerror(errno));
		return (-1);
    }
	printf("Bind connected\n");

    // listen to the socket

	if (listen(sockfd, BACKLOG) == -1)
    {
    	printf("Error in listen: %s", strerror(errno));
		return (-1);
    }
	printf("Listening...\n");

    // now accept an incoming connection:

    addr_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    if (new_fd == -1)
    {
		printf("Error in accept: %s", strerror(errno));
		return (-1);
    }
	printf("Accepting...\n");
	freeaddrinfo(res);
	return (0);
}
