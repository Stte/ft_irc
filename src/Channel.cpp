#include "Channel.hpp"

Channel::Channel(std::string const &name, Client &client) : name(name), modes(0), limit(0)
{
	// do name check?
	this->clients[client.get_nickname()] = &client;
	this->ops.push_back(client.get_nickname());
}

void Channel::join(Client &client)
{
	if (!invite_check(client))
	{
		std::cerr << "Client could not join channel: invite only" << std::endl;
		return;
	}
	if (!key_check(client))
	{
		std::cerr << "Client could not join channel: wrong key" << std::endl;
		return;
	}
	if (!limit_check())
	{
		std::cerr << "Client could not join channel: channel is full" << std::endl;
		return;
	}
	if (this->clients[client.get_nickname()] != NULL)
	{
		std::cerr << "Client could not join channel: client already in channel" << std::endl;
		return;
	}
	this->clients[client.get_nickname()] = &client;
	// broadcast a message to all clients in the channel that the client has joined
}

void Channel::invite(const std::string &commander, std::string const &nickname)
{
	if (!is_op(commander))
	{
		std::cerr << "Client could not invite: not an op" << std::endl;
		return;
	}
	if (std::find(this->invite_list.begin(), this->invite_list.end(), nickname) == this->invite_list.end())
		this->invite_list.push_back(nickname);
	// send message to client that he has been invited
}

void Channel::mode(int action, const std::string &commander, std::string const &mode)
{
	if (!is_op(commander))
	{
		std::cerr << "Client could not set mode: not an op" << std::endl;
		return;
	}
	if (action == ADD)
		add_mode(mode);
	else if (action == REMOVE)
		remove_mode(mode);
}

int main()
{
	Client client("test", "test1", 1);
	Channel channel("test", client);

	Client client2("test2", "test2", 2);
	channel.mode(ADD, client2.get_nickname(), "i");
	channel.mode(ADD, client.get_nickname(), "i");
	channel.join(client2);

	// print clients
	std::map<std::string, Client *> clients = channel.get_clients();
	for (std::map<std::string, Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		std::cout << it->first << " => " << it->second->get_nickname() << std::endl;
	}

	channel.invite(client.get_nickname(), "test2");
	channel.join(client2);

	// print clients
	clients = channel.get_clients();
	for (std::map<std::string, Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		std::cout << it->first << " => " << it->second->get_nickname() << std::endl;
	}

	// print modes
	std::cout << "Modes: " << (int)channel.get_modes() << std::endl;

	return 0;
}
