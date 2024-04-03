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
#include "Channel.hpp"
#include <memory>
#include <map>

#define RED "\033[1;31m"
#define WHITE "\033[0;37m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"

enum rType
{
	ChannelToClients,
	ClientToClient,
	ClientToChannel,
	ServerToClient,
};

class Client;
class Channel;
class Message;
class Server
{
private:
	int port;
	std::string name;
	const std::string password;
	int server_socket;
	static bool signal;
	std::vector<Client *> clients;
	std::vector<struct pollfd> fds;
	std::map<std::string, Channel *> channels;
	Client *findClient(std::string &nickname) const;

public:
	Server(int port, const std::string &password);
	~Server();

	// Getters
	Client *get_client(int fd);
	Client *get_client(std::string nickname);
	std::string get_name();
	std::vector<std::string> get_clients_channel(std::string const &nickname);

	// Methods
	void create_server_socket();
	void server_init();
	void close_fds();
	void accept_new_client();
	void receive_new_data(int fd);
	void remove_client(int fd);
	void remove_channel(Channel *channel);
	static void handle_signal(int sig);
	void send_response(std::string response, int fd);
	void send_response(rType responseType, std::string sender, std::string recipient, std::string response);
	std::vector<std::string> split_recived_buffer(std::string str);
	void exec_cmd(Message &newmsg, int fd);
	bool nickname_in_use(std::string &nickname);
	bool is_valid_nickname(std::string &nickname);


	// CMDS
	void nick(std::string nickname, int fd);
	void username(std::vector<std::string> username, int fd);
	void join(Message &cmd, int fd);
	void pass(std::string pass, int fd);
	void quit(int fd);
	void quit(Message &cmd, int fd);
	void privmsg(Message &cmd, int fd);
	void mode(Message &cmd, int fd);
	void invite(Message &cmd, int fd);
	void topic(Message &cmd, int fd);
	void kick(Message &cmd, int fd);
};

#endif
