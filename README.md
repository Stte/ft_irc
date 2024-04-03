# ft_irc

This repository contains the implementation of an Internet Relay Chat (IRC) server in C++. The server allows users to connect, communicate, and interact with each other in real-time through chat rooms (channels). Users can join different channels, send messages, and perform various IRC commands.

## Getting Started

To get started with this project, you'll need to have a C++ compiler. The project uses a Makefile for building and compiling.

### Prerequisites

- C++ compiler (e.g., g++)
- Terminal or command prompt
- [Download and install](https://irssi.org/download/) Irssi as your client
- For using the bot `pip3 install requests`

### Building the Project

1. Clone the repository `git clone https://github.com/Stte/ft_irc.git`
2. Navigate to the project directory `cd ft_irc`
3. Run `make` to compile the project.

### Running the Server

1. After building the project, run the server executable `./ircserv <port> <password>`. Replace `<port>` and `<password>` following the IRC protocol rules.
2. The server will start listening for incoming connections on the specified port.

## Using the IRC Server

### Connecting to the Server

We chose to implement our IRC server to work with [Irssi](https://irssi.org/) as our client.

1. Open your terminal.
2. Run `irssi`.
3. Connect to the server by typing `/connect localhost <port> <password>`. Replace with the port and password you chose.

### IRC Commands

#### PASS

Syntax: `PASS password`

Used to authenticate the user with the server. Replace `password` with the actual password.

#### NICK

Syntax: `NICK nickname`

Used to set or change the user's nickname. Replace `nickname` with the desired nickname.

#### USER

Syntax: `USER username hostname servername :realname`

Used to specify the username, hostname, servername, and real name of the user.

#### JOIN

Syntax: `JOIN #channelname`

Used to join a channel. Replace `channelname` with the name of the channel you want to join. If the channel does not exist it will create it.

#### MODE

Syntax: `MODE #channelname +/- o nickname` - Give/take channel operator privilege.
Syntax: `MODE #channelname +/- i` - Set/remove Invite-only channel.
Syntax: `MODE #channelname +/- t` -  Set/remove the restrictions of the TOPIC command to channel operators.
Syntax: `MODE #channelname +/- k password` - Set/remove the channel key (password).
Syntax: `MODE #channelname +/- l limit` - Set/remove the user limit to channel.

Used to change the mode of a channel or user.

#### KICK

Syntax: `KICK #channelname nickname`

Used to remove a user from a channel. Replace `channelname` with the name of the channel and `nickname` with the nickname of the user to be kicked.

#### INVITE

Syntax: `INVITE nickname #channelname`

Used to invite a user to a channel. Replace `nickname` with the nickname of the user and `channelname` with the name of the channel.

#### PRIVMSG

Syntax: `PRIVMSG #channelname/nickame message`

Used to send a private message to a user or a message to a channel. Replace `channelname` or `nickname` with the name of the channel or the nickname of the user, and `message` with the message you want to send.

#### QUIT

Syntax: `QUIT`

Used to disconnect from the server.

#### TOPIC

Syntax: `TOPIC #channelname topic`

Used to set or view the topic of a channel. Replace `channelname` with the name of the channel and `topic` with the new topic.

#### PART

Syntax: `PART #channelname`

Used to leave a channel. Replace `channelname` with the name of the channel.

### Using the Bot

The `bot.py` script is a simple IRC bot that can join channels, respond to messages, and fetch random quotes from the Game of Thrones.

1. Ensure you have Python3 installed.
2. Run the bot script by typing `python3 bot.py` in your terminal.
3. The bot will connect to the server and join a channel. You can interact with it by sending messages in the channel.

## Contributors

- [@DeRuina](https://github.com/DeRuina)
- [@Stte](https://github.com/Stte)
- [@Doxakis1](https://github.com/Doxakis1)
