#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <csignal>
#include <memory>
#include "Channel.hpp"

class Channel;
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
	std::string hostname;
	std::string realname;
	std::vector<Channel *> channels;

public:
	Client();
	Client(std::string nickname, std::string username, int fd);

	// Setters
	void set_fd(int fd);
	void set_IPaddr(std::string IPaddr);
	void set_buffer(std::string buff);
	void set_nickname(std::string &nickname);
	void set_hostname(std::string &hostname);
	void set_realname(std::string &realname);
	void set_username(std::string &username);
	void set_registered(bool value);
	void set_logged_in(bool value);

	// Getter
	int get_fd() const;
	bool is_registered();
	bool is_logged_in();
	std::string get_nickname() const;
	std::string get_username() const;
	std::string get_buffer() const;
	std::string get_IPaddr() const;
	std::string get_hostname() const;
	std::string get_realname() const;
	std::vector<Channel *> get_channels() const;

	// Add
	void add_channel(Channel *channel);

	// Remove
	void remove_channel(Channel *channel);

	// Methods
	void clear_buffer();
};

#endif
