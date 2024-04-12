#include "Server.hpp"
#include "Channel.hpp"

// Closing all the client fd's and the server socket
void Server::close_fds()
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		std::cout << RED << "Client <" << clients[i]->get_fd() << "> Disconnected" << WHITE << std::endl;
		close(clients[i]->get_fd());
	}
	if (this->server_socket != -1)
	{
		std::cout << RED << "Server " << this->server_socket << " disconnected" << WHITE << std::endl;
		close(this->server_socket);
	}
}

// Removing client from vectors
void Server::remove_client(int fd)
{

	for (std::vector<pollfd>::iterator it = this->fds.begin(); it != this->fds.end(); ++it)
	{
		if (it->fd == fd)
		{
			this->fds.erase(it);
			break;
		}
	}
	for (std::vector<Client *>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		if ((*it)->get_fd() == fd)
		{
			delete *it;
			this->clients.erase(it);
			break;
		}
	}
}
void Server::remove_channel(Channel *channel)
{
	this->channels.erase(channel->get_channel_name());
	delete channel;
}

// Signal handler
void Server::handle_signal(int sig)
{
	std::cout << std::endl
			  << "Signal Received!" << std::endl;
	(void)sig;
	Server::signal = true;
}
// Sending response to the client
void Server::send_response(std::string response, int fd)
{
	std::cout << "Response:\n"
			  << response;
	if (send(fd, response.c_str(), response.size(), 0) == -1)
		std::cerr << "Response send() faild" << std::endl;
}

Client *Server::findClient(std::string &nickname) const
{
	for (auto &client : clients)
	{
		if (client->get_nickname() == nickname)
			return client;
	}
	return nullptr;
}

void Server::send_response(rType responseType, std::string sender, std::string recipient, std::string response)
{
	switch (responseType)
	{
	case rType::ChannelToClients:
	{
		auto ch = channels[recipient];
		if (!ch)
			return;
		auto clients = ch->get_clients();
		size_t size = clients.size();
		for (size_t i = 0; i < size; i++)
		{
			if (send(clients[i]->get_fd(), response.c_str(), response.size(), 0) == -1)
				std::cerr << "Response send() failed to user: " << clients[i]->get_nickname() << std::endl;
		}
		return;
		break;
	}
	case rType::ClientToChannel:
	{
		auto ch = channels[recipient];
		if (!ch)
			return;
		auto clients = ch->get_clients();
		size_t size = clients.size();
		for (size_t i = 0; i < size; i++)
		{
			if (clients[i]->get_nickname() == sender)
				continue;
			if (send(clients[i]->get_fd(), response.c_str(), response.size(), 0) == -1)
				std::cerr << "Response send() failed to user: " << clients[i]->get_nickname() << std::endl;
		}
		return;
		break;
	}
	case rType::ClientToClient:
	case rType::ServerToClient:
	{
		const Client *findRecipient = findClient(recipient);
		if (findRecipient == nullptr)
		{
			const Client *findSender = findClient(sender);
			if (findSender == nullptr)
			{
				std::cerr << "Server failed to locate sender: " << sender << std::endl;
				return;
			}
			response = ERR_ERRONEUSNICK(recipient);
			if (send(findSender->get_fd(), response.c_str(), response.size(), 0) == -1)
				std::cerr << "Response send() failed to user: " << findSender->get_nickname() << std::endl;
			return;
		}
		else
		{
			if (send(findRecipient->get_fd(), response.c_str(), response.size(), 0) == -1)
				std::cerr << "Response send() failed to user: " << findRecipient->get_nickname() << std::endl;
		}
		return;
	}
	}
}
// Get the specific client
Client *Server::get_client(int fd)
{
	for (size_t i = 0; i < this->clients.size(); i++)
		if (this->clients[i]->get_fd() == fd)
			return (this->clients[i]);
	return (NULL);
}

// Get the specific client
Client *Server::get_client(std::string nickname)
{
	for (size_t i = 0; i < this->clients.size(); i++)
		if (this->clients[i]->get_nickname() == nickname)
			return (this->clients[i]);
	return (NULL);
}

// Get server name
std::string Server::get_name()
{
	return (this->name);
}
// Spliting each of clients input to vector of vector of strings
std::vector<std::string> Server::split_recived_buffer(std::string str)
{
	size_t pos;

	std::vector<std::string> vec;
	std::istringstream input(str); // creating input streamm for getline
	std::string line;
	while (std::getline(input, line))
	{
		pos = line.find_first_of("\r\n");
		if (pos != std::string::npos)
			line = line.substr(0, pos);
		vec.push_back(line);
	}
	return (vec);
}
std::vector<std::string> Server::get_clients_channel(std::string const &nickname)
{
	std::vector<std::string> clients_channels;
	for (auto it = this->channels.begin(); it != this->channels.end(); ++it)
		if (it->second->is_client_in_channel(nickname) == true)
			clients_channels.push_back(it->first);
	return clients_channels;
}
