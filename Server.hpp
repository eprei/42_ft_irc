#ifndef SERVER_HPP
# define SERVER_HPP

# include <netinet/in.h>
# include <iostream>
# include "Client.hpp"
# include <vector>
# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>

class Server
{
	public:

		Server();
		Server(Server &other);
		Server &operator=(Server &other);
		~Server();

		bool checkArgs(int argc, char **argv);
		bool printCorrectUse() const;

		void launchServ();

	private:

		std::string				_password;
		int						_port;
		std::vector<Client *>	_clientsList;
		int						_serverSocket;
		struct sockaddr_in		_serverAddress;
		fd_set					_currentSockets;
		fd_set					_readySockets;
		int						_nOfClients;
};

#endif
