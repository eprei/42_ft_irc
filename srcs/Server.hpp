#ifndef SERVER_HPP
# define SERVER_HPP

# include "Includes.hpp"

class Client;
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
		void	removeClient(Client* client);
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

		void 		printChannel(std::string channel_name);
		Channel*	getChannel(std::string channel_name);
		void	createChannel(Client* client, std::string channel_name);
		void	removeChannel(std::string channel_name);
		void	addClientToChannel(Client* client, std::string channel_name);
		void	removeClientFromChannel(Client* client, std::string channel_name);
		bool	channelExists(std::string channel_name);
		bool	isNickUsed(std::string nickname);
		Client		*getClient(std::string nickname);
		std::string	getServInfo( void ) const;
		std::string	isOper(Client *client);

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
