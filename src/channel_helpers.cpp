#include "Channel.hpp"

/// CLIENTS ///

std::vector<std::shared_ptr<Client>> Channel::get_clients() const
{
	return (this->clients);
}

std::shared_ptr<Client> Channel::get_client(std::string const &nickname)
{
	for (const auto &client : clients)
	{
		if (client->get_nickname() == nickname)
			return (client);
	}
	return (nullptr);
}

std::shared_ptr<Client> Channel::get_client(std::shared_ptr<Client> client)
{
	for (const auto &c : clients)
	{
		if (c == client)
			return (c);
	}
	return (nullptr);
}

void Channel::add_client(std::shared_ptr<Client> client)
{
	if (get_client(client->get_nickname()) != nullptr)
	{
		std::cerr << "Client already in channel" << std::endl;
		return;
	}
	this->clients.push_back(client);
}

void Channel::remove_client(std::string const &nickname)
{
	std::shared_ptr<Client> client = get_client(nickname);
	if (!client)
	{
		std::cerr << "Client not in channel" << std::endl;
		return;
	}
	this->clients.erase(std::remove(this->clients.begin(), this->clients.end(), client), this->clients.end());
	// send message to client that he has been kicked
}

/// OPS ///

std::vector<std::shared_ptr<Client>> Channel::get_ops() const
{
	return (this->ops);
}

std::shared_ptr<Client> Channel::get_op(std::string const &nickname)
{
	for (const auto &op : ops)
	{
		if (op->get_nickname() == nickname)
			return (op);
	}
	return (nullptr);
}

std::shared_ptr<Client> Channel::get_op(std::shared_ptr<Client> client)
{
	for (const auto &op : ops)
	{
		if (op == client)
			return (op);
	}
	return (nullptr);
}

void Channel::add_op(std::shared_ptr<Client> client)
{
	if (get_op(client->get_nickname()) != nullptr)
	{
		std::cerr << "Client already op" << std::endl;
		return;
	}
	this->ops.push_back(client);
}

void Channel::remove_op(std::string const &nickname)
{
	std::shared_ptr<Client> op = get_op(nickname);
	if (!op)
	{
		std::cerr << "Client not op" << std::endl;
		return;
	}
	this->ops.erase(std::remove(this->ops.begin(), this->ops.end(), op), this->ops.end());
}

/// INVITES ///

std::shared_ptr<Client> Channel::get_invite(std::string const &nickname)
{
	for (const auto &invite : invite_list)
	{
		if (invite->get_nickname() == nickname)
			return (invite);
	}
	return (nullptr);
}

std::shared_ptr<Client> Channel::get_invite(std::shared_ptr<Client> client)
{
	for (const auto &invite : invite_list)
	{
		if (invite == client)
			return (invite);
	}
	return (nullptr);
}

void Channel::add_invite(std::shared_ptr<Client> client)
{
	if (get_invite(client->get_nickname()) != nullptr)
	{
		std::cerr << "Client already invited" << std::endl;
		return;
	}
	this->invite_list.push_back(client);
}

void Channel::remove_invite(std::string const &nickname)
{
	std::shared_ptr<Client> client = get_invite(nickname);
	if (!client)
	{
		std::cerr << "Client not invited" << std::endl;
		return;
	}
	this->invite_list.erase(std::remove(this->invite_list.begin(), this->invite_list.end(), client), this->invite_list.end());
}

/// GETTERS ///

unsigned char Channel::get_modes()
{
	return (this->modes);
}

/// SETTERS ///

void Channel::set_key(std::shared_ptr<Client> commander, std::string const &key)
{
	if (!get_op(commander))
	{
		std::cerr << "Client could not set key: not an op" << std::endl;
		return;
	}
	this->key = key;
}

void Channel::set_limit(std::shared_ptr<Client> commander, unsigned int limit)
{
	if (!get_op(commander))
	{
		std::cerr << "Client could not set limit: not an op" << std::endl;
		return;
	}
	this->limit = limit;
}

/// INVITE CHECK ///

/// @brief Checks if the channel is invite only and if the client is in the invite list
/// @param client
/// @return true if the channel is not invite only or if the client is in the invite list
bool Channel::invite_check(std::shared_ptr<Client> client)
{
	if (this->modes & MODE_I) // if channel is invite only
	{
		if (get_invite(client) != nullptr)
			return (true); // if client is in invite list
		return (false);	   // if client is not in invite list
	}
	return (true); // if channel is not invite only
}

/// @brief Checks if the channel is key protected and if the client has the correct key
/// @param key string
/// @return true if the channel is not key protected or if the client has the correct key
bool Channel::key_check(std::string const &key) // todo: check if this is correct
{
	if (this->modes & MODE_K) // if channel is key protected
	{
		if (this->key == key)
			return (true); // if client has the correct key
		return (false);	   // if client has the wrong key
	}
	return (true); // if channel is not key protected
}

/// @brief Checks if the channel has a user limit and if the channel is full
/// @return true if the channel has no user limit or if the channel is not full
bool Channel::limit_check()
{
	if (this->modes & MODE_L) // if channel has a user limit
	{
		if (this->clients.size() < this->limit)
			return (true); // if the channel is not full
		return (false);	   // if the channel is full
	}
	return (true); // if channel has no user limit
}

/// MODES ///

void Channel::add_mode(char const &mode)
{
	if (mode == 'i')
		this->modes |= MODE_I;
	else if (mode == 'k')
		this->modes |= MODE_K;
	else if (mode == 'l')
		this->modes |= MODE_L;
	else
		std::cerr << "Unknown mode" << std::endl;
}

void Channel::remove_mode(char const &mode)
{
	if (mode == 'i')
		this->modes &= ~MODE_I;
	else if (mode == 'k')
		this->modes &= ~MODE_K;
	else if (mode == 'l')
		this->modes &= ~MODE_L;
	else
		std::cerr << "Unknown mode" << std::endl;
}

void Channel::broadcast(std::string const &message)
{
	std::cout << "Broadcasting: " << message << std::endl;
	server.send_response(rType::ChannelToClients, "P0INTL655", name, message);
}

void Channel::broadcast(std::shared_ptr<Client> sender, std::string const &message)
{
	std::cout << "Broadcasting: " << message << std::endl;
	server.send_response(rType::ClientToChannel, sender->get_nickname(), name, message);
}
bool Channel::is_client_in_channel(std::string const &nickname)
{
	for (size_t i = 0; i < this->clients.size(); i++)
		if (clients[i]->get_nickname() == nickname)
			return (true);
	return (false);
}

std::string Channel::get_channel_name()
{
	return (this->name);
}
