#include "Server.hpp"

// Closing all the client fd's and the server socket
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
    for (std::vector<Client>::iterator it = this->clients.begin(); it != this->clients.end(); ++it) 
		{
        if (it->get_fd() == fd)
				{
            this->clients.erase(it);
            break; 
        }
    }
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

void Server::send_response(rType responseType, std::string recipient, std::string response)
{
	bool sent = false;
	switch (responseType)
	{
		case rType::ClientToChannel:
		// for (auto ch : channels)
		// {
		// 	if (ch.get_name() == recipient)
		//	{
		// 		for (auto e ; ch.clients)
		// 		{
		// 			if (send(e.get_fd(), response.c_str(), response.size(), 0) == -1)
		//				std::cerr << "Response send() faild to user: " << e.get_nickname() << std::endl;
		// 		}
		//	}
		//	return ;
		//
		// }
		break ;
		case rType::ClientToClient:
		case rType::ServerToClient:
		{
			for (auto e : clients)
			{
				if (e.get_nickname() ==  recipient)
				{
					if (send(e.get_fd(), response.c_str(), response.size(), 0) == -1)
					{
						std::cerr << "Response send() faild to user:" << e.get_nickname() << std::endl;
						return ; 
					}
						
				}	
			}
			return ; // I am thinking here it should throw, because so the requester gets a notification that user was not found
		}
	}
}
// Get the specific client
Client *Server::get_client(int fd)
{
	for (size_t i = 0; i < this->clients.size(); i++)
		if (this->clients[i].get_fd() == fd)
			return (&this->clients[i]);
	return (NULL);
}
// Get server name
std::string Server::get_name()
{
	return (this->name);
}
// // Spliting each of clients input to vector of vector of strings
std::vector<std::string> Server::split_recived_buffer(std::string str)
{
	size_t	pos;

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
// Spliting the input to strings
// std::vector<std::string> Server::split_cmd(std::string cmd)
// {
// 	std::vector<std::string> vec;
// 	std::istringstream input(cmd); // input stream to get every token
// 	std::string token;
// 	while (input >> token)
// 	{
// 		vec.push_back(token);
// 		token.clear();
// 	}
// 	return (vec);
// }
