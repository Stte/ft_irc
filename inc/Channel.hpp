#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "Client.hpp"

#define MODE_I 0b00000001
#define MODE_K 0b00000010
#define MODE_L 0b00000100

enum ModeAction
{
	REMOVE,
	ADD
};

class Channel
{
public:
	Channel(std::string const &name, Client &client);

	void join(Client &client);
	// void part(Client &client);
	void invite(std::string const &commander, std::string const &nickname); // maybe Client &commander
	// void kick(Client &commander, std::string const &nickname);
	void mode(int action, std::string const &commander, std::string const &mode);	// Client &commander
	void op(int action, std::string const &commander, std::string const &nickname); // Client &commander
	// void topic(Client &client, std::string const &topic);

	std::map<std::string, Client *> get_clients() const;
	std::vector<std::string> get_ops() const;
	unsigned char get_modes();

	// void set_key(std::string const &key);
	void set_limit(unsigned int limit);

	bool is_op(std::string const &commander); // Client &commander

private:
	std::string name;
	std::map<std::string, Client *> clients;
	std::vector<std::string> ops;
	std::vector<std::string> invite_list;
	std::string key;
	unsigned char modes;
	unsigned int limit;

	bool invite_check(Client &client);
	bool key_check(Client &client);
	bool limit_check();

	void add_mode(std::string const &mode);
	void remove_mode(std::string const &mode);
};
#endif
