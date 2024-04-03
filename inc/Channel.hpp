#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include <vector>
#include <algorithm>
#include "Server.hpp"
#include <memory>

#define MODE_I 0b00000001
#define MODE_K 0b00000010
#define MODE_L 0b00000100

#define NO_KEY std::string()

enum ModeAction
{
	REMOVE,
	ADD,
	VIEW
};

class Client;
class Server;
class Channel
{
public:
	Channel(std::string const &name, Client *client, Server &server);

	void join(Client *client, std::string const &key);
	// void part(Client &client);
	void invite(Client *commander, std::string const &nickname);
	void kick(Client *commander, std::string const &nickname);
	void kick(Client *commander, std::string const &nickname, std::string const &msg);
	void mode(Client *commander, int action, char const &mode);
	void op(Client *commander, int action, std::string const &nickname);
	void topic(Client *commander);
	void topic(Client *commander, int action, std::string const &topic);
	void quit(Client *commander);
	void quit(Client *commander, std::string const &msg);
	void message(Client *sender, std::string const &message);

	void broadcast(std::string const &message);
	void broadcast(Client *sender, std::string const &message);

	std::vector<Client *> get_clients() const;
	std::vector<Client *> get_ops() const;
	unsigned char get_modes();
	std::string get_topic() const;

	void set_key(Client *commander, std::string const &key);
	void set_limit(Client *commander, unsigned int limit);
	void set_topic(std::string topic);

	bool is_client_in_channel(std::string const &nickname);
	std::string get_channel_name();

	// bool is_op(Client* client);
	bool is_empty();

private:
	Channel();
	std::string name;
	Server &server;
	std::vector<Client *> clients;
	std::vector<Client *> ops;
	std::vector<Client *> invite_list;
	std::string key;
	std::string topic_str;
	unsigned char modes;
	unsigned int limit;

	bool invite_check(Client *client);
	bool key_check(std::string const &key);
	bool limit_check();

	void add_mode(char const &mode);
	void remove_mode(char const &mode);

	Client *get_client(Client *client);
	Client *get_client(std::string const &nickname);
	void add_client(Client *client);
	void remove_client(std::string const &nickname);
	void remove_client(Client *client);

	Client *get_op(Client *client);
	Client *get_op(std::string const &nickname);
	void add_op(Client *client);
	void remove_op(std::string const &nickname);
	void remove_op(Client *client);

	Client *get_invite(Client *client);
	Client *get_invite(std::string const &nickname);
	void add_invite(Client *client);
	void remove_invite(std::string const &nickname);
	void remove_invite(Client *client);
};
#endif
