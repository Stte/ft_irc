#ifndef SERVER_H
#define SERVER_H

#include "Client.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <csignal>
#include <cstring>
#include "Replays.hpp"

#define RED "\e[1;31m"
#define WHITE "\e[0;37m"
#define GREEN "\e[1;32m"
#define YELLOW "\e[1;33m"

class Server
{
	private:
		int port;
		std::string name;
		const std::string password;
		int server_socket;
		static bool signal;
		std::vector<Client> clients;
		std::vector<struct pollfd> fds;


	public:
		Server(int port, const std::string &password);


		//Getters
		Client *get_client(int fd);
		std::string get_name();

		//Methods
		void create_server_socket();
		void server_init();
		void close_fds();
		void accept_new_client();
		void receive_new_data(int fd);
		void remove_client(int fd);
		static void handle_signal(int sig);
		void send_response(std::string response, int fd);
		std::vector<std::vector<std::string>> split_recived_buffer(std::string str);
		void exec_cmd(std::vector<std::string> cmd, int fd);
		std::vector<std::string> split_cmd(std::string cmd);
		bool nickname_in_use(std::string &nickname);
		bool is_valid_nickname(std::string &nickname);

		// CMDS
		void nick(std::string nickname, int fd);
		void username(std::vector<std::string> username, int fd);
		void join(std::string cmd, int fd);

};

#endif
