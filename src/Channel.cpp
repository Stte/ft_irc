#include "Channel.hpp"

Channel::Channel() : name(""), server(*(new Server(0, ""))), modes(0), limit(0)
{
}

Channel::Channel(std::string const &name, Client &client, Server &server) : name(name), server(server), modes(0), limit(0)
{
	// do name check?
	// check that server is valid
	this->clients[client.get_nickname()] = &client;
	this->ops.push_back(client.get_nickname());
}

void Channel::join(Client &client, std::string const &key)
{
	if (!invite_check(client))
	{
		std::cerr << "Client could not join channel: invite only" << std::endl;
		return;
	}
	if (!key_check(key))
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
	// server.send_response(RPL_JOINMSG(client.get_username(), client.get_IPaddr(), this->name), client.get_fd());
}

void Channel::invite(Client &commander, std::string const &nickname)
{
	if (!is_op(commander))
	{
		std::cerr << "Client could not invite: not an op" << std::endl;
		return;
	}
	// check if client exists
	// if (server.get_client(nickname) == NULL)
	// {
	// 	std::cerr << "Client could not invite: client does not exist" << std::endl;
	// 	return;
	// }

	if (std::find(this->invite_list.begin(), this->invite_list.end(), nickname) == this->invite_list.end())
		this->invite_list.push_back(nickname);
	// send message to client that he has been invited
}

void Channel::kick(Client &commander, std::string const &nickname)
{
	if (!is_op(commander))
	{
		std::cerr << "Client could not kick: not an op" << std::endl;
		return;
	}
	this->clients.erase(nickname);
	// send message to client that he has been kicked
}

void Channel::mode(Client &commander, int action, std::string const &mode)
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

void Channel::op(Client &commander, int action, std::string const &nickname)
{
	if (!is_op(commander))
	{
		std::cerr << "Client could not op: not an op" << std::endl;
		return;
	}
	if (action == ADD)
	{
		if (std::find(this->ops.begin(), this->ops.end(), nickname) == this->ops.end())
			this->ops.push_back(nickname);
	}
	else if (action == REMOVE)
	{
		this->ops.erase(std::remove(this->ops.begin(), this->ops.end(), nickname), this->ops.end());
	}
	// todo: messages?
}

void Channel::topic(Client &commander, int action, std::string const &topic)
{
	(void)topic;
	if (action == ADD)
	{
		if (!is_op(commander))
		{
			std::cerr << "Client could not set topic: not an op" << std::endl;
			return;
		}
		// set topic
	}
	else if (action == REMOVE)
	{
		if (!is_op(commander))
		{
			std::cerr << "Client could not remove topic: not an op" << std::endl;
			return;
		}
		// remove topic
	}
	// view topic
}

void Channel::broadcast(std::string const &message)
{

	for (std::map<std::string, Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		(void)message;
		// server.send_response(RPL_BROADCASTMSG(it->first, this->name, message), it->second->get_fd());
	}
}
