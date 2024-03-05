NAME = ircserv

SRC = main.cpp Server.cpp Client.cpp

FLAGS = -Wall -Wextra -Werror -std=c++98

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRC)
	@c++ $(FLAGS) -o $(NAME) $(SRC)

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME) client

re: fclean all

client: client.cpp
	@c++ $(FLAGS) -o client client1.cpp

debug: FLAGS += -g
debug: re
