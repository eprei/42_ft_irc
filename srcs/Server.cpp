# include "Server.hpp"

bool go = true;

Server::Server(): _name("*.42irc.net"){}

Server::Server(Server &other){ *this = other;}

Server &Server::operator=(Server &other)
{
	this->_name = other._name;
	this->_password = other._password;
	this->_port = other._port;
	this->_serverSocket = other._serverSocket;
	this->_serverAddress = other._serverAddress;
	this->_currentSockets = other._currentSockets;
	this->_readySockets = other._readySockets;
	this->_clientsList = other._clientsList;
	this->_channelList = other._channelList;
	this->_buf = other._buf;
	this->_serverInfo = other._serverInfo;
	this->_startTime = other._startTime;

	return (*this);
}

Server::~Server(){
	// TO DO: delete all mallocs like _clientList.seconds and _channelList objects
}

bool	Server::finish()
{
    std::cout << "\nTerminating server...\n";
	std::map<int , Client *>::iterator it = this->_clientsList.begin();
	for ( ; it != this->_clientsList.end(); it++)
		this->removeClientFromServer(it->second, "");
    close(getServerSocket()); // cerrar el socket
    return (true); // salir del programa con el codigo de señal
	// for (std::vector<Channel *>::iterator it = _channelList.begin(); it != _channelList.end(); it++)
	// // removeChannel((*it)->getName());
	// {
	// 	delete *it; // Liberamos la memoria reservada para el canal
    //     _channelList.erase(it);
	// }
}

bool	Server::checkArgs(int argc, char **argv){
	if (argc != 3 || !(DEFAULT_MIN_PORT <= atoi(argv[1]) && atoi(argv[1]) <= DEFAULT_MAX_PORT))
		return printCorrectUse();
	_port = atoi(argv[1]);
	_password = argv[2];
	return EXIT_SUCCESS;
}

bool	Server::printCorrectUse() const
{
	std::cout << "Correct use of ircserv: ./ircserv <port> <password>" << std::endl;
	std::cout << "<port> must be a number between 6665-6669" << std::endl;
	// Choix des ports en fonction de l'article https://fr.wikipedia.org/wiki/Internet_Relay_Chat
	return EXIT_FAILURE;
}

bool	Server::launchServ(){
	if (serverSocketConfig())
		return (EXIT_FAILURE);
	if (serverLoop())
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	Server::serverSocketConfig(){
	time(&_startTime);
//	SOCKET CREATION
	if ((_serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		std::cout << "ERROR: socket function error" << std::endl;
		return (EXIT_FAILURE);
	}

//	INITIALIZE THE SERVER'S ADDRESS STRUCTURE
	bzero(&_serverAddress.sin_zero, sizeof(_serverAddress));
	this->_serverAddress.sin_family = AF_INET;
	this->_serverAddress.sin_port = htons(this->_port);
	this->_serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	// bzero(&(_serverAddress.sin_zero), 8);

	int enable = 1;
	if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
    	perror("setsockopt(SO_REUSEADDR) failed");
}
//	BIND SOCKET WITH A PORT
	if ((bind(_serverSocket, (struct sockaddr *)&_serverAddress, sizeof(_serverAddress))) < 0){
		perror("\nerror found at bind");
		return (EXIT_FAILURE);
	}
// LISTEN
	if ((listen(_serverSocket, MAX_CONNECTIONS_ON_STANDBY)) < 0){
		perror("\nerror found at listen");
		return (EXIT_FAILURE);
	}

// SET THE GROUPS OF FD THAT WILL BE CHECKED BY SELECT
	FD_ZERO(&_currentSockets);
	FD_SET(this->_serverSocket, &_currentSockets);

	std::cout << *this << std::endl;

	return (EXIT_SUCCESS);
}

bool	isSocketClosed(int socket_fd)
{
	char buffer[1];
	int result = recv(socket_fd, buffer, 1, MSG_PEEK);

	if (result == 0)
		return true;
	else if (result < 0) {
		// std::cout << "error found at isSocketClosed function" << std::endl;
		return false;
	}
	else
		return false;
}

void	signalHandler(int signum)
{
	if (signum == SIGINT)
		go = false;
}

bool Server::serverLoop(){
	std::cout << FC(BOLDGREEN, "IRC_SERVER initialized... Welcome") << std::endl;
	while (1)
	{
		if (signal(SIGINT, signalHandler) == SIG_ERR)
			std::cerr << "error while handling signal" << std::endl;
		bzero(&_readySockets, sizeof(_readySockets));
		_readySockets = _currentSockets;
		if (select(FD_SETSIZE, &_readySockets, NULL, NULL, NULL) < 0)
		{
			// EINTR = A signal was delivered before the time limit expired and before any of the selected events occurred
			 if (errno == EINTR) //---> To verify if we control errno or not because if we do we could go against what is requested in the evaluation
			  {
                // Si se recibe una señal durante select(), volver a comprobar go
                if (!go) {
                    break;
                }
            } else {
			perror("\nerror found at select"); // TO CONSIDER: We must decide how to deal with this error and consider to throw exceptions or kill the program ???
			return (EXIT_FAILURE); // TO DO: this EXIT is temporary since we do not have the right to use the EXIT function, we must handle it differently.
            }
		}

		for (int SocketNumber = 0; SocketNumber < FD_SETSIZE; SocketNumber++)
		{
			if (FD_ISSET(SocketNumber, &_readySockets))
			{
				if (SocketNumber == _serverSocket)
					addNewClient();
				else
				{
					if (isSocketClosed(SocketNumber) == true)
						removeClientFromServer(_clientsList[SocketNumber], " has been disconnected unexpectedly");
					else
					{
						messageHandling(SocketNumber);
						if (_clientsList[SocketNumber]->isQuiting())
							removeClientFromServer(_clientsList[SocketNumber], "QUIT ");
					}
				}
			}
		}
		std::cout << FC(BOLDGREEN, "CHECK INACTIVE USERS ") << std::endl;
		checkInactiveUsers();
		usleep(600);
	}
	finish();
	return (EXIT_SUCCESS);
}

// CLIENTS CLIENTS CLIENTS CLIENTS CLIENTS CLIENTS CLIENTS CLIENTS
// CLIENTS CLIENTS CLIENTS CLIENTS CLIENTS CLIENTS CLIENTS CLIENTS
// CLIENTS CLIENTS CLIENTS CLIENTS CLIENTS CLIENTS CLIENTS CLIENTS

void	Server::messageHandling(int userSocketNumber){
	char bufferLocal[MAX_BUFF + 1];
	ssize_t  numOfBytesReceived;

	bzero(bufferLocal, MAX_BUFF + 1);
	numOfBytesReceived = recv( userSocketNumber, bufferLocal, MAX_BUFF, 0);
	if (numOfBytesReceived < 0)
	{
		std::cout << "ERROR: recv function error" << std::endl; // TO CONSIDER: We must decide how to deal with this error and consider to throw exceptions or kill the program ???
		// return (EXIT_FAILURE); // TO DO: this EXIT is temporary since we do not have the right to use the EXIT function, we must handle it differently.
	}
	else
	{
		_buf.append(bufferLocal);
		_clientsList[userSocketNumber]->setBuf(_buf);
	}
	_buf.erase();
}


void	Server::checkInactiveUsers(){
	if (!_clientsList.empty())
	{
		std::vector<Client *>				toDeleteList;
		std::map<int , Client *>::iterator	it = _clientsList.begin();
		std::map<int , Client *>::iterator	itEnd = _clientsList.end();

		while( it != itEnd )
		{
			if (it->second->getIdle() > TIMEOUT)
				toDeleteList.push_back(it->second);
			++it;
		}
		for (size_t i = 0; i < toDeleteList.size(); i++)
		{
			std::string part_msg = " has been disconnected from the server due to inactivity";

			std::string msg = toDeleteList.at(i)->formatMsgsUsers();
			msg.append("QUIT : " + toDeleteList.at(i)->getNickname() + part_msg + END_CHARACTERS);
			toDeleteList.at(i)->sendMsg(msg);
			toDeleteList.at(i)->sendMsgSharedUsers(msg);
			toDeleteList.at(i)->leaveAll();

			removeClientFromServer(toDeleteList.at(i), " TIMOUT DISCONNECTED");
		}
	}
}

void	Server::addNewClient(){
	int addrSize = sizeof(struct sockaddr_in);
	int clientSocketLocal;
	struct sockaddr_in clientAddr;
	Client *neo = new Client(this);

	if ((clientSocketLocal = accept(this->_serverSocket, (struct sockaddr*)&clientAddr, (socklen_t*)&addrSize)) < 0){
		perror("\nerror found at accept"); // TO CONSIDER: We must decide how to deal with this error and consider to throw exceptions or kill the program ???
		delete neo;
		return ;
	}
	neo->setSocket(clientSocketLocal);
	neo->setAddress(clientAddr);
	neo->setIp(inet_ntoa(clientAddr.sin_addr));
	_clientsList.insert(std::pair<int , Client *>(neo->getSocket(), neo));
	FD_SET(clientSocketLocal, &_currentSockets);
	std::cout << FC(GREEN, "++++++\tClient ") << neo->getId() << " added\t++++++\n";
}

void	Server::removeClientFromServer(Client* client, std::string reason){

	std::cout << YELLOW << "\tClient " << client->getId() << " " << reason << WHITE << std::endl;

	int sock = client->getSocket();

	close(sock);
	delete _clientsList.at(sock);
	FD_CLR(sock, &_currentSockets);
	_clientsList.erase(sock);
	std::cout << GREEN << ">>\t\tCLIENT REMOVED" << "\t\t<<" << RESET << std::endl;
}


bool	Server::isNickUsed(std::string nickname)
{
	std::map<int , Client *>::iterator itBegin = _clientsList.begin();

	while (itBegin != _clientsList.end())
	{
		if (itBegin->second->getNickname() == nickname)
			return true;
		itBegin++;
	}
	return false;
}

std::string	Server::isOper(Client *client)
{
	for (size_t i = 0; i < _channelList.size(); i++)
	{
		if (_channelList[i]->isOperator(client) == true)
			return "is an IRC operator";
	}
	return "is not an operator";
}

// CHANNELS CHANNELS CHANNELS CHANNELS CHANNELS CHANNELS CHANNELS CHANNELS
// CHANNELS CHANNELS CHANNELS CHANNELS CHANNELS CHANNELS CHANNELS CHANNELS
// CHANNELS CHANNELS CHANNELS CHANNELS CHANNELS CHANNELS CHANNELS CHANNELS

bool	Server::channelExists(std::string channel_name)
{
    for (size_t i = 0; i < _channelList.size(); i++)
    {
        if (_channelList[i]->getName() == channel_name)
        {
            return true;
        }
    }
    return false;
}

void	Server::createChannel(Client* owner, std::string channel_name)
{
    if (channelExists(channel_name))
    {
        std::cout << "Channel " << channel_name << " already exists." << std::endl;
        return;
    }

    Channel* new_channel = new Channel(*owner, channel_name);
    _channelList.push_back(new_channel);
    std::cout << "Channel " << channel_name << " created." << std::endl;
}

void	Server::removeChannel(std::string channel_name)
{
	std::vector<Channel *>::iterator it = _channelList.begin();
    for ( ; it != _channelList.end(); ++it)
    {
        if ((*it)->getName() == channel_name)
        {
			// Channel *tmp = *it;
            // _channelList.erase(it); // Eliminamos el puntero al canal del vector
            // delete tmp; // Liberamos la memoria reservada para el canal
			delete *it; // Liberamos la memoria reservada para el canal
			_channelList.erase(it); // Eliminamos el puntero al canal del vector
            return;
        }
    }
}
			// std::cout << FC(RED, "LLEGAMOS AQUI????") << std::endl;

void	Server::addClientToChannel(Client* client, std::string channel_name)
{
    Channel* channel = getChannel(channel_name);
    if (channel == NULL)
    {
        std::cout << "Channel " << channel_name << " does not exist." << std::endl;
        return;
    }
	if (!channel->hasClient(client))
	{
    	channel->addClient(client);
		client->addJoinedChannel(channel);
	}
}

void	Server::removeClientFromChannel(Client* client, std::string channel_name)
{
    Channel* channel = getChannel(channel_name);
    if (channel == NULL)
    {
        std::cout << "Channel " << channel_name << " does not exist." << std::endl;
        return;
    }
    channel->removeClient(client);
	client->removeJoinedChannel(channel);
	if (channel->isEmpty())
		removeChannel(channel_name);
}

void	Server::printChannel(std::string channel_name)
{
    Channel* channel = getChannel(channel_name);
    if (channel == NULL)
    {
        std::cout << "Channel " << channel_name << " does not exist." << std::endl;
        return;
    }

    std::cout << "Channel " << channel_name << " info:" << std::endl;
    std::cout << "  - Name: " << channel->getName() << std::endl;
    std::cout << "  - Clients: " << std::endl;
    std::vector<Client*> clients = channel->getMembers();
    for (size_t i = 0; i < clients.size(); i++)
    {
        std::cout << "    - " << clients[i]->getNickname() << std::endl;
    }
}

// GETTERS GETTERS GETTERS GETTERS GETTERS GETTERS GETTERS GETTERS
// GETTERS GETTERS GETTERS GETTERS GETTERS GETTERS GETTERS GETTERS
// GETTERS GETTERS GETTERS GETTERS GETTERS GETTERS GETTERS GETTERS

time_t const*	Server::getStartTime() const { return &_startTime;}
std::string		Server::getName() const {return _name;}
std::string		Server::getPassword() const {return _password;}
std::string		Server::getServInfo() const{ return _serverInfo;}
int				Server::getPort() const {return _port;}
int				Server::getServerSocket() const {return _serverSocket;}
size_t			Server::getNOfClients() const { return _clientsList.size(); }

Client*			Server::getClient(std::string nickname)
{
	std::map<int , Client *>::iterator itBegin = _clientsList.begin();

	while (itBegin != _clientsList.end())
	{
		if (itBegin->second->getNickname() == nickname)
			return itBegin->second;
		itBegin++;
	}
	return NULL;
}

Channel*		Server::getChannel(std::string channel_name)
{
    for (size_t i = 0; i < _channelList.size(); i++)
    {
        if (_channelList[i]->getName() == channel_name)
        {
            return _channelList[i];
        }
    }
	return NULL;
}

std::vector<Channel *> *Server::getChannelList()
{
	return (&_channelList);
}

std::ostream		&operator<<( std::ostream & o, Server const & rhs )
{
	o << std::endl << FC(YELLOW, "******\tServer info\t******") << std::endl;
	o << "Name: " << rhs.getName() << std::endl;
	o << "Password: " << rhs.getPassword() << std::endl;
	o << "Port: " << rhs.getPort() << std::endl;
	o << "Server Socket: " << rhs.getServerSocket() << std::endl;
	o << "Number of clients: " << rhs.getNOfClients() << std::endl;
	o << "Created: " << ctime(rhs.getStartTime()) << std::endl;
	return o;
}
