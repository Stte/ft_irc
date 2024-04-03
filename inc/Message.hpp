#ifndef MESSAGE_H
#define MESSAGE_H

#include "Client.hpp"
#include "Server.hpp"
#include "Replays.hpp"
#include <string>
#include <vector>

enum IRCCommand {
    JOIN,
    NICK,
    USER,
    PASS,
    CAP,
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
    void parse();
public:
    Message(const std::string& msg);
    std::string getPrefix() const;
    IRCCommand getCommand() const;
    std::vector<std::string> getParams() const;
    const std::string &getRawCmd();
};

#endif
