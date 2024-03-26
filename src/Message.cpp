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

Message::Message(const std::string& msg) : rawMessage(msg) {
    Message::parse();
}

std::string Message::getPrefix() const { return prefix; }
IRCCommand Message::getCommand() const { return command; }
std::vector<std::string> Message::getParams() const { return params; }
const std::string &Message::getRawCmd(){ return rawCmd; }

void Message::parse()
{
        // std::cout << rawMessage << std::endl;
        size_t prefixEnd = 0;
        if (rawMessage[0] == ':') {
            prefixEnd = rawMessage.find(' ');
            prefix = rawMessage.substr(1, prefixEnd - 1);
            prefixEnd++;
        } // this might not necessarily exist as per irc rules, prefixes are not mandatory

        // Find command
        size_t commandEnd = rawMessage.find(' ', prefixEnd);
        rawCmd = rawMessage.substr(prefixEnd, commandEnd - prefixEnd);
        command = assignCommand(rawCmd);
        // if (command == IRCCommand::ERROR)
        //     throw something maybe
        size_t start = commandEnd + 1;

        while (start < rawMessage.length()) {
            // std::cout << "start is: " << start << std::endl;
            size_t end;
            if (rawMessage[start] == ':') {
                end = rawMessage.length(); // ':' indicates always end of message so ':' to last character is last parameter
            } else {
                end = rawMessage.find(' ', start); // for example in case: :Teemu KICK #channel Dean :Reason for kick
                if (end == rawMessage.npos)
                    end = rawMessage.length();
            }
            params.push_back(rawMessage.substr(start, end - start));
            start = end + 1;
       }
}
