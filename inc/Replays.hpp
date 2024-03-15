#ifndef REPLAYS_H
#define REPLAYS_H

#define CRLF "\r\n"

// replays

#define RPL_CONNECTED(nickname) (": 001 " + nickname + " : Welcome to the IRC server!" + CRLF)
#define RPL_NICKCHANGE(oldnickname, nickname) (":" + oldnickname + " NICK " + nickname + CRLF)


//ERRORS

#define ERR_NOTENOUGHPARAM(nickname) (": 461 " + nickname + " :Not enough parameters." + CRLF)
#define ERR_NOTREGISTERED(servername) (": 451 " + servername + " :Register first!" + CRLF)
#define ERR_NICKINUSE(nickname) (": 433 " + nickname + " :Nickname is already in use" + CRLF)
#define ERR_ERRONEUSNICK(nickname) (": 432 " + nickname + " :Erroneus nickname" + CRLF)
#define ERR_ALREADYREGISTERED(nickname) (": 462 " + nickname + " :You are already registered!" + CRLF)
#define ERR_INCORPASS(nickname) (": 464 " + nickname + " :Password incorrect! try again!" + CRLF )


#endif
