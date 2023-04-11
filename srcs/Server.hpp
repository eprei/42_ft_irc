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

		// server TCP
		bool		finish();
		bool		checkArgs(int argc, char **argv);
		bool		printCorrectUse() const;
		bool		launchServ();
		bool		serverSocketConfig();
		bool		serverLoop();
		
		// CLIENT
		void		checkInactiveUsers();
		void		messageHandling(int userSocketNumber);
		void		addNewClient();
		void		removeClientFromServer(Client* client, std::string reason);
		bool		isNickUsed(std::string nickname);
		std::string	isOper(Client *client);

		// CHANNEL
		bool		channelExists(std::string channel_name);
		void		createChannel(Client* client, std::string channel_name);
		void		removeChannel(std::string channel_name);
		void		addClientToChannel(Client* client, std::string channel_name);
		void		removeClientFromChannel(Client* client, std::string channel_name);
		void 		printChannel(std::string channel_name);

		// GETTERS
		// struct sockaddr_in	getServerAddress() const; // TO CONSIDER if it's useful
		time_t		const *getStartTime() const;
		std::string	getName() const;
		std::string	getPassword() const;
		std::string	getServerState() const;
		std::string	getServInfo() const;
		int			getPort() const;
		int			getServerSocket() const;
		int			getNOfClients() const;
		Client*		getClient(std::string nickname);
		Channel*	getChannel(std::string channel_name);
		std::vector<Channel *> *getChannelList();



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
		std::string					_serverInfo;
		time_t						_startTime;
};

std::ostream	&operator<<( std::ostream & o, Server const & rhs );

#endif
