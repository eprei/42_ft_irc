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
# define CLIENT_NICKNAME_NOT_SET "NickNotSet"
# define CLIENT_USERNAME_NOT_SET "UserNotSet"
# define CLIENT_HOSTNAME_NOT_SET "HostnameNotSet"
# define CLIENT_REALNAME_NOT_SET "RealnameNotSet"
# define USERSMODES		"io"
# define CHANNELSMODES	"kobil"
# define NUMBER_OF_CMD 19
# define END_CHARACTERS "\r\n"
# define TIMEOUT 60.0
# define REFRESH_INTERVAL 1
# define PASS_NOT_YET_ENTERED 0
# define PASS_WRONG 1

# include <stdlib.h>
# include <unistd.h>
# include <iostream>

# include <string>
# include <string.h>
# include <sstream>
# include <vector>
# include <set>
# include <map>

# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <signal.h>
# include <ctime>
# include <errno.h>
# include <arpa/inet.h>
# include <time.h>
# include <fcntl.h>

# include "Message.hpp"
# include "Client.hpp"
# include "Server.hpp"
# include "Channel.hpp"
# include "Colors.hpp"
# include "numeric_macros.hpp"
# include "Utils.hpp"

#endif //INCLUDES_HPP
