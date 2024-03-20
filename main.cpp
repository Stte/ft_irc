#include "Server.hpp"
#include "Client.hpp"


int arg_check(const std::string &port, const std::string &pass)
{
	if (pass.size() > 10)
	{
		std::cerr << RED << "Invalid password, password can't be longer than 10 characters" << WHITE << std::endl;
		return (1);
	}
	try
	{
		int portnum = std::stoi(port);
		if (portnum < 1024 || portnum > 65535)
		{
			std::cerr << RED << "invalid port - range (1024 - 65535)" << WHITE << std::endl;	
			return (1);
		}
	}
	catch(std::exception &e)
	{
		std::cerr << RED << "invalid port" << WHITE << std::endl;
	}
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Wrong args - ./ircserv port password" << std::endl;
		return (1);
	}
	std::cout << YELLOW << "---- IRC SERVER ----" << WHITE << std::endl;
	if (arg_check(argv[1], argv[2]))
		return (1);
	Server serv(std::stoi(argv[1]), argv[2]);
	try
	{
		std::signal(SIGINT, Server::handle_signal);
		std::signal(SIGQUIT, Server::handle_signal);
		serv.server_init();
	}
	catch (std::exception &e)
	{
		serv.close_fds();
		std::cerr << e.what() << std::endl;
	}
	std::cout << YELLOW << "Server Closed!" << WHITE << std::endl;
	return (0);
}
