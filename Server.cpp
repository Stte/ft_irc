#include "Server.hpp"

bool Server::signal = false;

Server::Server(int port, const std::string &password)
	: port(port), password(password)
{
	this->server_socket = -1;
}

void Server::create_server_socket()
{
	struct pollfd	new_poll;
	int				optset;

	struct sockaddr_in6 addr; // sockaddr_in6 for dual-stack socket ipv6 & ipv4
	memset(&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;        // set the address family to ipv6
	addr.sin6_addr = in6addr_any;      // set the address to any local machine address
	addr.sin6_port = htons(this->port);// convert the port to network byte order
	this->server_socket = socket(AF_INET6, SOCK_STREAM, 0);// create the server socket
	if (this->server_socket == -1) // check if created
		throw(std::runtime_error("failed to create socket"));
	optset = 0;
	if (setsockopt(this->server_socket, IPPROTO_IPV6, IPV6_V6ONLY, &optset,
			sizeof(optset)) == -1) // Set the IPV6_V6ONLY option to 0 to allow ipv4 (dual-stack socket)
		throw(std::runtime_error("failed to set IPV6_V6ONLY option"));
	optset = 1;
	if (setsockopt(this->server_socket, SOL_SOCKET, SO_REUSEADDR, &optset,
			sizeof(optset)) == -1) // Set the SO_REUSEADDR option to allow the socket to reuse the address
		throw(std::runtime_error("failed to set option (SO_REUSEADDR) on socket"));
	if (fcntl(this->server_socket, F_SETFL, O_NONBLOCK) == -1) // set the socket option (O_NONBLOCK) for non-blocking socket
		throw(std::runtime_error("faild to set option (O_NONBLOCK) on socket"));
	if (bind(this->server_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) // bind the socket to the address
		throw(std::runtime_error("faild to bind socket"));
	if (listen(this->server_socket, SOMAXCONN) == -1) // listen for incoming connections and making the socket a passive socket
		throw(std::runtime_error("listen() faild"));
	new_poll.fd = this->server_socket; // add the server socket to the pollfd
	new_poll.events = POLLIN;          //set the event to POLLIN for reading data
	new_poll.revents = 0;              // set the revents to 0
	this->fds.push_back(new_poll);     // add the server socket to the pollfd
}

void Server::server_init()
{
	create_server_socket();
	std::cout << GREEN << "Server " << this->server_socket << " Connected" << WHITE << std::endl;
	std::cout << "Waiting to accept a connection..." << std::endl;
	while (this->signal == false) // run the server until the signal is received
	{
		if ((poll(&this->fds[0], this->fds.size(), -1) == -1)
			&& this->signal == false) // wait for an event
			throw(std::runtime_error("poll() faild"));
		for (size_t i = 0; i < this->fds.size(); i++) // check all fd's
		{
			if (this->fds[i].revents & POLLIN) // check if there is data to read
			{
				if (this->fds[i].fd == this->server_socket)
					accept_new_client(); // accept new client
				else
					receive_new_data(this->fds[i].fd); // receive new data from a registered client
			}
		}
	}
	close_fds(); // close the fd's when the server gets signal and breaks the loop
}

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

void Server::accept_new_client()
{
	Client usr; // create a new client
	struct sockaddr_in usraddr;
	struct pollfd new_poll;
	socklen_t len = sizeof(usraddr);

	int usr_fd = accept(this->server_socket, (sockaddr *)&(usraddr), &len); // accept the new client
	if (usr_fd == -1)
	{
		std::cout << "accept() failed" << std::endl; 
		return;
	}
	if (fcntl(usr_fd, F_SETFL, O_NONBLOCK) == -1) // set the socket option (O_NONBLOCK) for non-blocking socket
	{
		std::cout << "fcntl() failed" << std::endl; 
		return;
	}

	new_poll.fd = usr_fd; // add the client socket to the pollfd
	new_poll.events = POLLIN; // set the event to POLLIN for reading data
	new_poll.revents = 0; //  set the revents to 0

	usr.set_fd(usr_fd); // set the client fd
	usr.set_IPaddr(inet_ntoa((usraddr.sin_addr))); // convert the ip address to string and set it
	clients.push_back(usr); // add the client to the vector of clients
	fds.push_back(new_poll); // add the client socket to the fd's vector

	std::cout << GREEN << "Client <" << usr_fd << "> Connected" << WHITE << std::endl;
}

void Server::receive_new_data(int fd)
{

	char buff[1024]; // buffer for the received data
	memset(buff, 0, sizeof(buff)); // clear the buffer

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1 , 0); // receive the data

	if (bytes <= 0)  // check if the client disconnected
	{
		std::cout << RED << "Client <" << fd << "> Disconnected" << WHITE << std::endl;
		remove_client(fd); // remove from clients vector and fd's vector
		close(fd); // close the client socket
	}
	else //print the received data
	{ 
		buff[bytes] = '\0';
		std::cout << YELLOW << "Client <" << fd << "> Data:" << WHITE << std::endl << buff;
		// HERE WE ADD OUR PARCING FUNCTIONS AND DO THE PARCING
	}
}

void Server::remove_client(int fd)
{
	for(size_t i = 0; i < this->fds.size(); i++)
	{ 
		if (this->fds[i].fd == fd)
		{
			this->fds.erase(this->fds.begin() + i); 
			break;
		}
	}
	for(size_t i = 0; i < this->clients.size(); i++)
	{ 
		if (this->clients[i].get_fd() == fd)
		{
			this->clients.erase(this->clients.begin() + i); 
			break;
		}
	}
}
