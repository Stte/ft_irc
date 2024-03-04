#ifndef SERVER_H
#define SERVER_H

#include "Client.hpp"
#include <iostream>
#include <vector> //-> for vector
#include <sys/socket.h> //-> for socket()
#include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in
#include <fcntl.h> //-> for fcntl()
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //-> for inet_ntoa()
#include <poll.h> //-> for poll()
#include <csignal> //-> for signal()

class Server
{
	private:
		int port;
		int server_socket;
		static bool signal;
		std::vector<Client> clients;
		std::vector<struct pollfd> fds;


	public:
		Server(std::string port, std::string &password);
		~Server();

};

#endif
