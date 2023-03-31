# CXX = c++
CXX = clang++
# CXX = g++-12

NAME = ircserv

SRCS =	./srcs/main.cpp\
		./srcs/Server.cpp\
		./srcs/Channel.cpp\
		./srcs/Client.cpp\
		./srcs/parsing.cpp\
		./srcs/numeric_reply.cpp\
		./commands/pass.cpp\
		./commands/nick.cpp\
		./commands/user.cpp\

SRCS_T =./test/clientTest1.cpp\
		./test/clientTest2.cpp\

CFLAGS = -Werror -Wextra -Wall -std=c++98
CFLAGS += -Wfatal-errors  #-pedantic
CFLAGS += -fsanitize=address -g3

OBJ = $(SRCS:.cpp=.o)
OBJ_T = $(SRCS_T:.cpp=.o)

TEST_CLIENT_1 = test1
TEST_CLIENT_2 = test2

.cpp.o:
	$(CXX) $(CFLAGS) -c $^ -o $@

all: $(NAME) $(TEST_CLIENT_1) $(TEST_CLIENT_2)

$(NAME): $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $(NAME)

$(TEST_CLIENT_1): $(OBJ_T)
	$(CXX) $(CFLAGS) ./test/clientTest1.cpp -o $(TEST_CLIENT_1)
 
$(TEST_CLIENT_2): $(OBJ_T)
	$(CXX) $(CFLAGS) ./test/clientTest2.cpp -o $(TEST_CLIENT_2)

run: all
	./ircserv 6667 asd

run2: all
	./ircserv 6668 asd

proxy: all
	python3 ./proxy/proxy.py

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(TEST_CLIENT_1)
	/bin/rm -f $(TEST_CLIENT_2)

re: fclean all test

.PHONY: all clean fclean re
