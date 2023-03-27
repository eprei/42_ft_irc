#ifndef INCLUDES_HPP
# define INCLUDES_HPP

# define FALSE 0
# define TRUE 1
# define MAX_BUFF 512
# define MAX_NICK_LENGTH 9
# define MAX_CONNECTIONS_ON_STANDBY 20
# define MAX_CHANNEL_PER_USER 10
# define DEFAULT_PORT 6667
# define DEFAULT_MIN_PORT 6665
# define DEFAULT_MAX_PORT 6669
# define DEFAULT_PASSWORD "0000"
# define IS_OFF "off"
# define IS_ON "on"
# define CLIENT_NICKNAME_NOT_SET "CLIENT_NICKNAME_NOT_SET"
# define CLIENT_USERNAME_NOT_SET "CLIENT_USERNAME_NOT_SET"
# define CLIENT_HOSTNAME_NOT_SET "CLIENT_HOSTNAME_NOT_SET"
# define NUMBER_OF_ACCEPTABLE_COMMANDS 13
# define END_CHARACTERS "\n"

# include <stdlib.h>
# include <iostream>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <errno.h>
# include <signal.h>

#define RESET		"\033[0m"
#define BLACK		"\033[30m"
#define RED			"\033[31m"
#define GREEN		"\033[32m"
#define YELLOW		"\033[33m"
#define BLUE		"\033[34m"
#define MAGENTA		"\033[35m"
#define CYAN		"\033[36m"
#define WHITE		"\033[37m"
#define BOLDBLACK	"\033[1m\033[30m"
#define BOLDRED		"\033[1m\033[31m"
#define BOLDGREEN	"\033[1m\033[32m"
#define BOLDYELLOW	"\033[1m\033[33m"
#define BOLDBLUE	"\033[1m\033[34m"
#define BOLDMAGENTA	"\033[1m\033[35m"
#define BOLDCYAN	"\033[1m\033[36m"
#define BOLDWHITE	"\033[1m\033[37m"

//  int g_server_is_on = TRUE;

#endif
