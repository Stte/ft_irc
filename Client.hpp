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
		bool registered;
		bool logged_in;
		std::string nickname;
		std::string username;
		std::string buffer;



	public:
		Client();
		Client(std::string nickname, std::string username, int fd);
		
		//Setters
		void set_fd(int fd);
		void set_IPaddr(std::string IPaddr);
		void set_buffer(std::string buff);
		void set_nickname(std::string &nickname);
		void set_username(std::string &username);
		void set_registered(bool value);
		void set_loggedin(bool value);

		// Getter
		int get_fd();
		bool get_registered();
		bool get_loggedin();
		std::string get_nickname();
		std::string get_username();
		std::string get_buffer();


		//Methods

		void clear_buffer();

};

#endif
