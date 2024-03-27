#include "Client.hpp"

Client::Client()
{
	this->nickname = "";
	this->username = "";
	this->fd = -1;
	this->registered = false;
	this->buffer = "";
	this->IPaddr = "";
}
Client::Client(std::string nickname, std::string username, int fd)
	: fd(fd), nickname(nickname), username(username)
{
}

int Client::get_fd() const
{
	return (this->fd);
}

std::string Client::get_nickname() const
{
	return (this->nickname);
}

void Client::clear_buffer()
{
	this->buffer.clear();
}

std::string Client::get_username() const
{
	return (this->username);
}

std::string Client::get_buffer() const
{
	return (this->buffer);
}

std::string Client::get_IPaddr() const
{
	return (this->IPaddr);
}

std::string Client::get_hostname() const
{
	return (this->hostname);
}

std::string Client::get_realname() const
{
	return (this->realname);
}

bool Client::is_registered()
{
	return (this->registered);
}

void Client::set_fd(int fd)
{
	this->fd = fd;
}

void Client::set_IPaddr(std::string IPaddr)
{
	this->IPaddr = IPaddr;
}

void Client::set_buffer(std::string buff)
{
	this->buffer += buff;
}

void Client::set_nickname(std::string &nickname)
{
	this->nickname = nickname;
}

void Client::set_username(std::string &username)
{
	this->username = username;
}

void Client::set_registered(bool value)
{
	this->registered = value;
}

void Client::set_hostname(std::string &hostname)
{
	this->hostname = hostname;
}

void Client::set_realname(std::string &realname)
{
	this->realname = realname;
}

std::vector<std::shared_ptr<Channel>> Client::get_channels() const
{
	return (this->channels);
}

void Client::add_channel(std::shared_ptr<Channel> channel)
{
	this->channels.push_back(channel);
}

void Client::remove_channel(std::shared_ptr<Channel> channel)
{
	this->channels.erase(std::remove(this->channels.begin(), this->channels.end(), channel), this->channels.end());
}
