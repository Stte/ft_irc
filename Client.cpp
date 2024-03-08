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
Client::Client(std::string nickname, std::string username, int fd) :fd(fd), nickname(nickname), username(username)
{
}

int Client::get_fd()
{
	return (this->fd);
}

std::string Client::get_nickname()
{
  return (this->nickname);
}

std::string Client::get_username()
{
  return (this->username);
}

std::string Client::get_buffer()
{
  return (this->buffer);
}

bool Client::get_registered()
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
