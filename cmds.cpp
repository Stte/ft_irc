#include "Server.hpp"

void Server::nick(std::vector<std::string> cmd, int fd)
{
	std::string used_nick;
	Client *user = get_client(fd);
	if (user && user->get_nickname().empty() && !user->get_registered() && user->get_username().empty())
	{
		user->set_nickname(cmd[1]);
		send_response(RPL_CONNECTED(user->get_nickname()), fd);
	}
}


