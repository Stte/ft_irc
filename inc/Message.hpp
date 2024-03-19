#ifndef MESSAGE_H
#define MESSAGE_H

#include "Client.hpp"
#include "Server.hpp"
#include "Replays.hpp"
#include <iostream>
#include <string>
#include <vector>

enum IRCCommand {
    JOIN,
    NICK,
    USER,
    PASS,
    CAP,
    MOTD,
    MODE,
    KICK,
    PING,
    PONG,
    INVITE,
    PRIVMSG,
    QUIT,
    TOPIC,
    PART,
    WHO,
    WHOIS,
    ERROR,
};

IRCCommand assignCommand(std::string cmd);

// Class to represent an IRC message
class Message {
private:
    std::string rawMessage;
    std::string prefix;
    std::string rawCmd;
    IRCCommand command;
    std::vector<std::string> params;

    void parse() {
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
        std::cout << "cmd" << rawCmd << std::endl;
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
public:
    Message(const std::string& msg) : rawMessage(msg) {
        parse();
    }
    std::string getPrefix() const { return prefix; }
    IRCCommand getCommand() const { return command; }
    std::vector<std::string> getParams() const { return params; }
    const std::string &getRawCmd(){ return rawCmd; }
};

#endif
