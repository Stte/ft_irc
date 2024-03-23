#include "Channel.hpp"

Channel::Channel() : name(""), server(*(new Server(0, ""))), modes(0), limit(0)
{
}

Channel::Channel(std::string const &name, std::shared_ptr<Client> client, Server &server) : name(name), server(server), modes(0), limit(0)
{
	// do name check?
	// check that server is valid
	add_client(client);
	add_op(client);
}

void Channel::join(std::shared_ptr<Client> client, std::string const &key)
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
	if (get_client(client->get_nickname()) != NULL)
	{
		std::cerr << "Client could not join channel: client already in channel" << std::endl;
		return;
	}
	add_client(client);
	broadcast(CLIENT(client->get_nickname(), client->get_username(), client->get_IPaddr()) + " JOIN " + this->name + CRLF);
}

void Channel::invite(std::shared_ptr<Client> commander, std::string const &nickname)
{
	if (!get_op(commander))
	{
		std::cerr << "Client could not invite: not an op" << std::endl;
		return;
	}
	if (server.get_client(nickname) == NULL)
	{
		std::cerr << "Client could not invite: client does not exist" << std::endl;
		return;
	}

	if (get_invite(nickname) == NULL)
	{
		std::shared_ptr<Client> client = server.get_client(nickname);
		if (client == NULL)
		{
			std::cerr << "Client could not invite: client does not exist" << std::endl;
			return;
		}
		add_invite(client);
	}
	// send message to client that he has been invited
}

void Channel::kick(std::shared_ptr<Client> commander, std::string const &nickname)
{
	if (!get_op(commander))
	{
		std::cerr << "Client could not kick: not an op" << std::endl;
		return;
	}
	remove_client(nickname);
}

void Channel::mode(std::shared_ptr<Client> commander, int action, std::string const &mode)
{
	if (!get_op(commander))
	{
		std::cerr << "Client could not set mode: not an op" << std::endl;
		return;
	}
	if (action == ADD)
		add_mode(mode);
	else if (action == REMOVE)
		remove_mode(mode);
}

void Channel::op(std::shared_ptr<Client> commander, int action, std::string const &nickname)
{
	if (!get_op(commander))
	{
		std::cerr << "Client could not op: not an op" << std::endl;
		return;
	}
	if (action == ADD)
	{
		if (get_op(nickname) == NULL)
		{
			std::shared_ptr<Client> client = server.get_client(nickname);
			if (client == NULL)
			{
				std::cerr << "Client could not op: client does not exist" << std::endl;
				return;
			}
			add_op(client);
		}
	}
	else if (action == REMOVE)
	{
		remove_op(nickname);
	}
	// todo: messages?
}

void Channel::topic(std::shared_ptr<Client> commander, int action, std::string const &topic)
{
	(void)topic;
	if (action == ADD)
	{
		if (!get_op(commander))
		{
			std::cerr << "Client could not set topic: not an op" << std::endl;
			return;
		}
		// set topic
	}
	else if (action == REMOVE)
	{
		if (!get_op(commander))
		{
			std::cerr << "Client could not remove topic: not an op" << std::endl;
			return;
		}
		// remove topic
	}
	// view topic
}

void Channel::message(std::shared_ptr<Client> sender, std::string const &message)
{
	if (get_client(sender) == NULL)
	{
		server.send_response(ERR_NOTONCHANNEL(this->name), sender->get_fd());
		return;
	}
	// Broadcasts to all exlude sender
	broadcast(sender, RPL_PRIVMSG(CLIENT(sender->get_nickname(), sender->get_username(), sender->get_IPaddr()), this->name, message));
}
