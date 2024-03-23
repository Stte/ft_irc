#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "Client.hpp"
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

class Server;
class Channel
{
public:
	Channel();
	Channel(std::string const &name, std::shared_ptr<Client> client, Server &server);

	void join(std::shared_ptr<Client> client, std::string const &key);
	// void part(Client &client);
	void invite(std::shared_ptr<Client> commander, std::string const &nickname);
	void kick(std::shared_ptr<Client> commander, std::string const &nickname);
	void mode(std::shared_ptr<Client> commander, int action, std::string const &mode);
	void op(std::shared_ptr<Client> commander, int action, std::string const &nickname);
	void topic(std::shared_ptr<Client> commander, int action, std::string const &topic);
	// void quit(std::string const &nickname);
	void message(std::shared_ptr<Client> sender, std::string const &message);

	std::map<std::string, std::shared_ptr<Client>> get_clients() const;
	std::vector<std::string> get_ops() const;
	unsigned char get_modes();

	void set_key(std::shared_ptr<Client> commander, std::string const &key);
	void set_limit(std::shared_ptr<Client> commander, unsigned int limit);

	bool is_op(std::shared_ptr<Client> client);

private:
	std::string name;
	Server &server;
	std::map<std::string, std::shared_ptr<Client>> clients;
	std::vector<std::string> ops;
	std::vector<std::string> invite_list;
	std::string key;
	unsigned char modes;
	unsigned int limit;

	bool invite_check(std::shared_ptr<Client> client);
	bool key_check(std::string const &key);
	bool limit_check();

	void add_mode(std::string const &mode);
	void remove_mode(std::string const &mode);

	void broadcast(std::string const &message);
};
#endif
