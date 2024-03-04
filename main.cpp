#include "Server.hpp"
#include "Client.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Wrong args - ./ircserv port password" << std::endl;
		return (1) ;
	}


	return (0);
}
