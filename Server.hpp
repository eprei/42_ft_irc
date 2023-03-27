#ifndef SERVER_HPP
# define SERVER_HPP

# include <netinet/in.h>
# include <iostream>
# include "Client.hpp"
# include <vector>
# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <map>
# include "Channel.hpp"
# include "Includes.hpp"

class Server
{
	public:

		Server();
		Server(Server &other);
		Server &operator=(Server &other);
		~Server();

		bool	checkArgs(int argc, char **argv);
		bool	printCorrectUse() const;

		bool	launchServ();
		bool	serverSocketConfig();
		bool	serverLoop();
		void	addNewClient();

		std::string		getName( void ) const;
		std::string		getPassword( void ) const;
		int				getPort( void ) const;
		int				getServerSocket( void ) const;
		// struct sockaddr_in	getServerAddress( void ) const; // TO CONSIDER if it's useful
		int				getNOfClients( void ) const;
		std::string		getServerState( void ) const;
		void			messageHandling(int userSocketNumber);

	private:

		std::string					_name;
		std::string					_password;
		int							_port;
		int							_serverSocket;
		struct sockaddr_in			_serverAddress;
		fd_set						_currentSockets;
		fd_set						_readySockets;
		int							_nOfClients; // TO RESOLVE: if is useful to have this info here or it's enough with Client::_maxId
		std::map<int , Client *>	_clientsList;
		std::vector<Channel *>		_channelList;
		std::string					_serverState;
		std::string					_buf;
};

std::ostream	&operator<<( std::ostream & o, Server const & rhs );

#endif
