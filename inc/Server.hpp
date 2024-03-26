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
#include "Message.hpp"
#include "Channel.hpp"
#include <memory>
#include <map>

#define RED "\e[1;31m"
#define WHITE "\e[0;37m"
#define GREEN "\e[1;32m"
#define YELLOW "\e[1;33m"

enum rType
{
	ChannelToClients,
	ClientToClient,
	ClientToChannel,
	ServerToClient,
};

class Channel;
class Server
{
private:
	int port;
	std::string name;
	const std::string password;
	int server_socket;
	static bool signal;
	std::vector<std::shared_ptr<Client>> clients;
	std::vector<struct pollfd> fds;
	std::map<std::string, std::shared_ptr<Channel>> channels;
	const std::shared_ptr<Client> findClient(std::string &nickname) const;


public:
	std::string hostname = "localhost"; // todo: change to actual hostname
	Server(int port, const std::string &password);

	// Getters
	std::shared_ptr<Client> get_client(int fd);
	std::shared_ptr<Client> get_client(std::string nickname);
	std::string get_name();
	std::vector<std::string> get_clients_channel(std::string const &nickname);

	// Methods
	void create_server_socket();
	void server_init();
	void close_fds();
	void accept_new_client();
	void receive_new_data(int fd);
	void remove_client(int fd);
	static void handle_signal(int sig);
	void send_response(std::string response, int fd);
	void send_response(rType responseType, std::string sender, std::string recipient, std::string response);
	std::vector<std::string> split_recived_buffer(std::string str);
	void exec_cmd(Message &newmsg, int fd);
	bool nickname_in_use(std::string &nickname);
	bool is_valid_nickname(std::string &nickname);

	// parser

	// CMDS
	void nick(std::string nickname, int fd);
	void username(std::vector<std::string> username, int fd);
	void join(Message &cmd, int fd);
	void pass(std::string pass, int fd);
	void quit(int fd);
	void privmsg(Message &cmd, int fd);
	void mode(Message &cmd, int fd);
	void invite(Message &cmd, int fd);
	// void part(Message &cmd, int fd);
	// void topic(Message &cmd, int fd);
	// void kick(Message &cmd, int fd);
};

#endif
