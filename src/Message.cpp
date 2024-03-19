#include "Server.hpp"
#include "Message.hpp"

IRCCommand assignCommand(std::string cmd)
{
    static const std::string array[18] ={ "JOIN", "NICK", "USER","PASS","CAP","MOTD","MODE","KICK","PING","PONG","INVITE","PRIVMSG","QUIT","TOPIC","PART","WHO","WHOIS", "ERROR"};
    for (int i = 0; i < IRCCommand::WHOIS; i++)
    {
        if (cmd == array[i])
            return (static_cast<IRCCommand>(i));
    }
    return IRCCommand::ERROR;
}