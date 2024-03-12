#include "Client.hpp"

Client::Client()
{
	this->nickname = "";
	this->username = "";
	this->fd = -1;
	this->registered = false;
	this->logged_in = false;
	this->buffer = "";
	this->IPaddr = "";
}
Client::Client(std::string nickname, std::string username, int fd)
	: fd(fd), nickname(nickname), username(username)
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

void Client::clear_buffer()
{
	this->buffer.clear();
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

bool Client::get_loggedin()
{
	return (this->logged_in);
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

void Client::set_loggedin(bool value)
{
	this->logged_in = value;
}
