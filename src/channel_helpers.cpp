#include "Channel.hpp"

bool Channel::is_op(Client &client)
{
	if (std::find(this->ops.begin(), this->ops.end(), client.get_nickname()) != this->ops.end())
		return (true);
	return (false);
}

/// GETTERS ///

std::map<std::string, Client *> Channel::get_clients() const
{
	return (this->clients);
}

std::vector<std::string> Channel::get_ops() const
{
	return (this->ops);
}

unsigned char Channel::get_modes()
{
	return (this->modes);
}

/// SETTERS ///

void Channel::set_key(Client &commander, std::string const &key)
{
	if (!is_op(commander))
	{
		std::cerr << "Client could not set key: not an op" << std::endl;
		return;
	}
	this->key = key;
}

void Channel::set_limit(Client &commander, unsigned int limit)
{
	if (!is_op(commander))
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
bool Channel::invite_check(Client &client)
{
	if (this->modes & MODE_I) // if channel is invite only
	{
		if (std::find(this->invite_list.begin(), this->invite_list.end(), client.get_nickname()) != this->invite_list.end())
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

void Channel::add_mode(std::string const &mode)
{
	if (mode == "i")
		this->modes |= MODE_I;
	else if (mode == "k")
		this->modes |= MODE_K;
	else if (mode == "l")
		this->modes |= MODE_L;
	else
		std::cerr << "Unknown mode" << std::endl;
}

void Channel::remove_mode(std::string const &mode)
{
	if (mode == "i")
		this->modes &= ~MODE_I;
	else if (mode == "k")
		this->modes &= ~MODE_K;
	else if (mode == "l")
		this->modes &= ~MODE_L;
	else
		std::cerr << "Unknown mode" << std::endl;
}

void Channel::broadcast(std::string const &message)
{
	std::cout << "Broadcasting: " << message << std::endl;
	for (std::map<std::string, Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		std::cout << "Sending to: " << it->first << " // fd: " << it->second->get_fd() << std::endl;
		server.send_response(message, it->second->get_fd());
	}
}
