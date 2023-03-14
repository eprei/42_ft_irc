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

# include <stdlib.h>
# include <iostream>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <errno.h>

#endif
