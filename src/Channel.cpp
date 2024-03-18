#include "Channel.hpp"

Channel::Channel(std::string const &name) : name(name)
{
}

/// @brief Checks if the channel is invite only and if the client is in the invite list
/// @param client
/// @return true if the channel is not invite only or if the client is in the invite list
bool Channel::invite_check(Client &client)
{
	if (this->mode & MODE_I) // if channel is invite only
	{
		if (this->inviteList.find(client.get_nickname()) != this->inviteList.end())
			return (true); // if client is in invite list
		return (false);	   // if client is not in invite list
	}
	return (true); // if channel is not invite only
}

/// @brief Checks if the channel is key protected and if the client has the correct key
/// @param client
/// @return true if the channel is not key protected or if the client has the correct key
bool Channel::key_check(Client &client) // todo: check if this is correct
{
	if (this->mode & MODE_K) // if channel is key protected
	{
		if (this->key == client.get_buffer())
			return (true); // if client has the correct key
		return (false);	   // if client has the wrong key
	}
	return (true); // if channel is not key protected
}

/// @brief Checks if the channel has a user limit and if the channel is full
/// @return true if the channel has no user limit or if the channel is not full
bool Channel::limit_check()
{
	if (this->mode & MODE_L) // if channel has a user limit
	{
		if (this->clients.size() < this->limit)
			return (true); // if the channel is not full
		return (false);	   // if the channel is full
	}
	return (true); // if channel has no user limit
}

void Channel::join(Client &client)
{
	if ()
	// this->clients[client.get_nickname()] = &client;
}
