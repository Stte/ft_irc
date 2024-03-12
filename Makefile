NAME = ircserv

SRC = main.cpp Server.cpp Client.cpp server_helpers.cpp cmds.cpp cmd_helpers.cpp

FLAGS = -Wall -Wextra -Werror -std=c++11

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRC)
	@c++ $(FLAGS) -o $(NAME) $(SRC)

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME) client

re: fclean all

client: client1.cpp
	@c++ $(FLAGS) -o client client1.cpp

debug: FLAGS += -g
debug: re
