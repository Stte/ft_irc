#include "Server.hpp"
#include "Client.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Wrong args - ./ircserv port password" << std::endl;
		return (1) ;
	}
	std::cout << "---- IRC SERVER ----" << std::endl;
	Server serv(std::stoi(argv[1]), argv[2]);
	try
	{
		serv.server_init();
	}
	catch (std::exception &e)
	{
		serv.close_fds();
		std::cerr << e.what() << std::endl;
	}


	return (0);
}
