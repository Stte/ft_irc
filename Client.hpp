#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <csignal>

class Client
{
	private:
		int fd;
		std::string IPaddr;


	public:
		Client();
		
		int get_fd();
		void set_fd(int fd);
		void set_IPaddr(std::string IPaddr);

};

#endif
