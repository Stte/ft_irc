#ifndef SERVER_H
#define SERVER_H

#include "Client.hpp"
#include "Server.hpp"
#include "Replays.hpp"
#include <iostream>
#include <string>
#include <vector>

// enum IRCCommand {
//     JOIN,
//     NICK,
//     USER,
//     PASS,
//     CAP,
//     MOTD,
//     MODE,
//     KICK,
//     PING,
//     PONG,
//     INVITE,
//     PRIVMSG,
//     QUIT,
//     TOPIC,
//     PART,
//     WHO,
//     WHOIS
// };


IRCCommand assignCmd(std::string cmd)
{
    static const std::string array[18] ={ "JOIN", "NICK", "USER","PASS","CAP","MOTD","MODE","KICK","PING","PONG","INVITE","PRIVMSG","QUIT","TOPIC","PART","WHO","WHOIS", "ERROR"};
    for (int i = 0; i < 16)
    {
        if (cmd == array[i])
            return (static_cast<IRCCommand>(i));
    }
    return IRCCommand::ERROR;
}
// Class to represent an IRC message
class Message {
private:
    std::string rawMessage;
    std::string prefix;
    IRCCommand command;
    std::vector<std::string> params;

    void parse() {
        size_t prefixEnd = rawMessage.find(' ');
        if (rawMessage[0] == ':') {
            prefix = rawMessage.substr(1, prefixEnd - 1);
            prefixEnd++;
        } // this might not necessarily exist as per irc rules, prefixes are not mandatory

        // Find command
        size_t commandEnd = rawMessage.find(' ', prefixEnd);
        std::string cmd = rawMessage.substr(prefixEnd, commandEnd - prefixEnd);
        command = assignCmd(cmd);
        // if (command == IRCCommand::ERROR)
        //     throw something maybe
        size_t start = commandEnd + 1;
        while (start < rawMessage.length()) {
            size_t end;
            if (rawMessage[start] == ':') {
                end = rawMessage.length(); // ':' indicates always end of message so ':' to last character is last parameter
            } else {
                end = rawMessage.find(' ', start); // for example in case: :Teemu KICK #channel Dean :Reason for kick
            }
            params.push_back(rawMessage.substr(start, end - start));
            start = end + 1;
        }
    }
public:
    Message(const std::string& msg) : rawMessage(msg) {
        parse();
    }
    std::string getPrefix() const { return prefix; }
    IRCCommand getCommand() const { return command; }
    std::vector<std::string> getParams() const { return params; }
};
