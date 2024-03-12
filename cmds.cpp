#include "Server.hpp"

void Server::nick(std::string nickname, int fd)
{
  size_t pos = nickname.find_first_not_of("\t\v ");
  if (pos != std::string::npos)
		nickname = nickname.substr(pos);
	Client *user = get_client(fd);
  if (pos == std::string::npos || nickname.empty())
  {
    this->send_response(ERR_NOTENOUGHPARAM(std::string("*")), fd);
    return ;
  }
  if (nickname_in_use(nickname) && user->get_nickname() != nickname)
  {
    std::string nick_in_use = "!";
    if (user->get_nickname().empty())
      user->set_nickname(nick_in_use);
    this->send_response(ERR_NICKINUSE(nickname), fd);
    return ; 
  }
  if (!is_valid_nickname(nickname))
  {
    this->send_response(ERR_ERRONEUSNICK(nickname), fd);
    return ;
  }
  else
  {
    if (user && user->get_registered())
    {
      std::string old_nick = user->get_nickname();
      user->set_nickname(nickname);
      if (!old_nick.empty() && old_nick  != nickname)
      {
        if (old_nick == "!" && !user->get_username().empty())
        {
          user->set_loggedin(true);
          this->send_response(RPL_CONNECTED(user->get_nickname()), fd);
          this->send_response(RPL_NICKCHANGE(user->get_nickname(), nickname), fd);
        }
        else
          this->send_response(RPL_NICKCHANGE(old_nick, nickname), fd);
        return ;
      }
    }
    else if (user && !user->get_registered())
      this->send_response(ERR_NOTREGISTERED(nickname), fd);
  }
  if (user && user->get_registered() && !user->get_username().empty() &&  !user->get_nickname().empty() && user->get_nickname() != "!" && !user->get_loggedin())
	{
		user->set_loggedin(true);
		this->send_response(RPL_CONNECTED(user->get_nickname()), fd);
	}
}


