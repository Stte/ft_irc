#include "Server.hpp"

void Server::close_fds()
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		std::cout << RED << "Client <" << clients[i].get_fd() << "> Disconnected" << WHITE << std::endl;
		close(clients[i].get_fd());
	}
	if (this->server_socket != -1)
	{
		std::cout << RED << "Server " << this->server_socket << " disconnected" << WHITE << std::endl;
		close(this->server_socket);
	}
}

void Server::remove_client(int fd)
{
	for (size_t i = 0; i < this->fds.size(); i++)
	{
		if (this->fds[i].fd == fd)
		{
			this->fds.erase(this->fds.begin() + i);
			break ;
		}
	}
	for (size_t i = 0; i < this->clients.size(); i++)
	{
		if (this->clients[i].get_fd() == fd)
		{
			this->clients.erase(this->clients.begin() + i);
			break ;
		}
	}
}

void Server::handle_signal(int sig)
{
	std::cout << std::endl
				<< "Signal Received!" << std::endl;
	(void)sig;
	Server::signal = true;
}

void Server::send_response(std::string response, int fd)
{
	std::cout << "Response:\n"
				<< response;
	if (send(fd, response.c_str(), response.size(), 0) == -1)
		std::cerr << "Response send() faild" << std::endl;
}

Client *Server::get_client(int fd)
{
	for (size_t i = 0; i < this->clients.size(); i++)
		if (this->clients[i].get_fd() == fd)
			return (&this->clients[i]);
	return (NULL);
} 

std::vector<std::vector<std::string>> Server::split_recived_buffer(std::string str)
{
	size_t	pos;

	std::vector<std::vector<std::string>> vec;
	std::istringstream input(str); // creating input streamm for getline
	std::string line;
	while (std::getline(input, line))
	{
		pos = line.find_first_of("\r\n");
		if (pos != std::string::npos)
			line = line.substr(0, pos);
		vec.push_back(split_cmd(line));
	}
	return (vec);
}

std::vector<std::string> Server::split_cmd(std::string cmd)
{
	std::vector<std::string> vec;
	std::istringstream input(cmd); // input stream to get every token
	std::string token;
	while (input >> token)
	{
		vec.push_back(token);
		token.clear();
	}
	return (vec);
}