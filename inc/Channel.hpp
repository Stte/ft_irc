#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include <map>
#include <vector>
#include "Client.hpp"

#define MODE_I 0b00000001
#define MODE_K 0b00000010
#define MODE_L 0b00000100

class Channel
{
public:
	Channel(std::string const &name);

	void join(Client &client);

private:
	std::string name;
	std::map<std::string, Client *> clients;
	std::vector<std::string> inviteList;
};
#endif
