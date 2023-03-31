# CXX = c++
CXX = clang++
# CXX = g++-12

NAME = ircserv

SRCS =	main.cpp\
		Server.cpp\
		Channel.cpp\
		Client.cpp\
		parsing.cpp\
		numeric_reply.cpp\
		pass.cpp\
		nick.cpp\
		user.cpp\
		whois.cpp\

CFLAGS = -Werror -Wextra -Wall -std=c++98
CFLAGS += -Wfatal-errors  #-pedantic
CFLAGS += -fsanitize=address -g3

OBJ = $(SRCS:.cpp=.o)

TEST_CLIENT_1 = test1
TEST_CLIENT_2 = test2

.cpp.o:
	$(CXX) $(CFLAGS) -c $^ -o $@

all: $(NAME) test

$(NAME): $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $(NAME)

test:
	$(CXX) $(CFLAGS) clientTest1.cpp -o $(TEST_CLIENT_1)
	$(CXX) $(CFLAGS) clientTest2.cpp -o $(TEST_CLIENT_2)

run: all
	./ircserv 6667 asd

run2: all
	./ircserv 6668 asd

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(TEST_CLIENT_1)
	/bin/rm -f $(TEST_CLIENT_2)

re: fclean all

.PHONY: all clean fclean re
