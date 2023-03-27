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
# include "Message.hpp"

class Channel;

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
		void	remove_client(Client* client);//hacer
		void	send_message_to_client(Client* client, std::string message);

		std::string		getName( void ) const;
		std::string		getPassword( void ) const;
		int				getPort( void ) const;
		int				getServerSocket( void ) const;
		// struct sockaddr_in	getServerAddress( void ) const; // TO CONSIDER if it's useful
		int				getNOfClients( void ) const;
		std::string		getServerState( void ) const;
		void			messageHandling(int userSocketNumber);
		
		void			numeric_reply(Client *c, std::string code);
		// void	handle_new_connection();
		// void	handle_client_request(Client* client);
		// IDEAS a implementar
		
		void	create_channel(std::string channel_name);
		void	add_client_to_channel(Client* client, std::string channel_name);
		void	remove_client_from_channel(Client* client, std::string channel_name);
		bool	channel_exists(std::string channel_name);
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

// };