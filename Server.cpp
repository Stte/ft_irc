#include "Server.hpp"

Server::Server(int port, const std::string &password)
	: port(port), password(password)
{
	this->server_socket = -1;
}

void Server::create_server_socket()
{
	struct sockaddr_in6 addr; // sockaddr_in6 for dual-stack socket ipv6 & ipv4
	struct pollfd new_poll;

	memset(&addr, 0, sizeof(addr));
    addr.sin6_family = AF_INET6; // set the address family to ipv4
 	addr.sin6_addr = in6addr_any; // set the address to any local machine address
 	addr.sin6_port = htons(this->port); // convert the port to network byte order

	this->server_socket = socket(AF_INET6, SOCK_STREAM, 0); // create the server socket
	if (this->server_socket == -1) // check if created
		throw (std::runtime_error("failed to create socket"));


	int optset = 0;
	if (setsockopt(this->server_socket, IPPROTO_IPV6, IPV6_V6ONLY, &optset, sizeof(optset)) == -1) // Set the IPV6_V6ONLY option to 0 to allow ipv4 (dual-stack socket)
		throw (std::runtime_error("failed to set IPV6_V6ONLY option"));
	optset = 1;
	if (setsockopt(this->server_socket, SOL_SOCKET, SO_REUSEADDR, &optset, sizeof(optset)) == -1) // Set the SO_REUSEADDR option to allow the socket to reuse the address
		throw (std::runtime_error("failed to set option (SO_REUSEADDR) on socket"));
	if (fcntl(this->server_socket, F_SETFL, O_NONBLOCK) == -1) //-> set the socket option (O_NONBLOCK) for non-blocking socket
		throw(std::runtime_error("faild to set option (O_NONBLOCK) on socket"));
	if (bind(this->server_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) // bind the socket to the address
		throw(std::runtime_error("faild to bind socket"));
	if (listen(this->server_socket, SOMAXCONN) == -1) // listen for incoming connections and making the socket a passive socket
		throw(std::runtime_error("listen() faild"));

	new_poll.fd = this->server_socket; //  add the server socket to the pollfd
	new_poll.events = POLLIN; //  set the event to POLLIN for reading data
	new_poll.revents = 0; // set the revents to 0
	this->fds.push_back(new_poll); // add the server socket to the pollfd
}

void Server::server_init()
{
	create_server_socket();

	std::cout << "Server" << this->server_socket << "Connected" << std::endl;
	std::cout << "Waiting to accept a connection..." << std::endl;

}
