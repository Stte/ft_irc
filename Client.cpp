#include "Client.hpp"

Client::Client()
{
}

int Client::get_fd()
{
	return (this->fd);
}

void Client::set_fd(int fd)
{
	this->fd = fd;
}

void Client::set_IPaddr(std::string IPaddr)
{
  this->IPaddr = IPaddr;
}
