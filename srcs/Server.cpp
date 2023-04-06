# include "Server.hpp"

bool go = true;

// TO DO: inicialice _serveInfo with the right timestamp info
Server::Server(): _name("*.42irc.net"), _nOfClients(0), _serverState(IS_ON){}

Server::Server(Server &other){ *this = other;}

Server &Server::operator=(Server &other)
{
	this->_password = other._password;
	this->_port = other._port;
	this->_clientsList = other._clientsList;
	return (*this);
}

Server::~Server(){
	// TO DO: delete all mallocs like _clientList.seconds and _channelList objects
}

bool Server::checkArgs(int argc, char **argv){
	if (argc != 3 || !(DEFAULT_MIN_PORT <= atoi(argv[1]) && atoi(argv[1]) <= DEFAULT_MAX_PORT))
		return printCorrectUse();
	_port = atoi(argv[1]);
	_password = argv[2];
	return EXIT_SUCCESS;
}

bool Server::printCorrectUse() const
{
	std::cout << "Correct use of ircserv: ./ircserv <port> <password>" << std::endl;
	std::cout << "<port> must be a number between 6665-6669" << std::endl;
	// Choix des ports en fonction de l'article https://fr.wikipedia.org/wiki/Internet_Relay_Chat
	return EXIT_FAILURE;
}

bool Server::launchServ(){
	if (serverSocketConfig())
		return (EXIT_FAILURE);
	if (serverLoop())
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool Server::serverSocketConfig(){
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

void Server::addNewClient(){
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
	std::cout << GREEN << "++++++\tClient " << neo->getId() << " added\t++++++\n";
	_nOfClients += 1;
}

void	Server::removeClient(Client* client){
	int sock = client->getSocket();

	close(sock);
	delete _clientsList[sock];
	FD_CLR(sock, &_currentSockets);
	_clientsList.erase(sock);
	_nOfClients -= 1;
	// TO DO: send messages to the corresponding channel after sendMsgToChannel() function is implemented
}

bool isSocketClosed(int socket_fd)
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
	std::cout << FC(BOLDRED, "IRC_SERVER initialized... Welcome") << std::endl;
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
						removeClient(_clientsList[SocketNumber]);
					else
						messageHandling(SocketNumber);
				}
			}
		}
		// TO DO: function to deconect all clients with timeout expired
		usleep(600);
	}
	finish();
	return (EXIT_SUCCESS);
}

void			Server::messageHandling(int userSocketNumber){

	char bufferLocal[MAX_BUFF + 1];
	ssize_t  numOfBytesReceived;

	bzero(bufferLocal, MAX_BUFF + 1);
	numOfBytesReceived = recv( userSocketNumber, bufferLocal, MAX_BUFF, 0);
	// _buf[numOfBytesReceived] = 0;
	if (numOfBytesReceived < 0){
		std::cout << "ERROR: recv function error" << std::endl; // TO CONSIDER: We must decide how to deal with this error and consider to throw exceptions or kill the program ???
		// return (EXIT_FAILURE); // TO DO: this EXIT is temporary since we do not have the right to use the EXIT function, we must handle it differently.
	}
	// bufferLocal[numOfBytesReceived] = 0;
	_buf.append(bufferLocal);
	_clientsList[userSocketNumber]->setBuf(_buf);
	_buf.erase();
	// std::cout << *this << std::endl;

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

Client	*Server::getClient(std::string nickname)
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

std::string		Server::getName( void ) const{return _name;}

std::string		Server::getPassword( void ) const{return _password;}

int				Server::getPort( void ) const{return _port;}

int				Server::getServerSocket( void ) const{return _serverSocket;}

int				Server::getNOfClients( void ) const {return _nOfClients;}

std::string		Server::getServerState( void ) const{return _serverState;}

time_t		const *Server::getStartTime( void ) const { return &_startTime;}

void Server::createChannel(Client* owner, std::string channel_name)
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

void Server::addClientToChannel(Client* to_add, std::string channel_name)
{
    Channel* channel = getChannel(channel_name);
    if (channel == NULL)
    {
        std::cout << "Channel " << channel_name << " does not exist." << std::endl;
        return;
    }
	if (!channel->hasClient(to_add))
    	channel->addClient(to_add);
}

void Server::removeClientFromChannel(Client* client, std::string channel_name)
{
    Channel* channel = getChannel(channel_name);
    if (channel == NULL)
    {
        std::cout << "Channel " << channel_name << " does not exist." << std::endl;
        return;
    }
    channel->removeClient(client);
	// if (channel->isEmpty())
	// 	removeChannel(channel_name);
}

void	Server::removeChannel(std::string channel_name)
{
    for (std::vector<Channel *>::iterator it = _channelList.begin(); it != _channelList.end(); ++it)
    {
        if ((*it)->getName() == channel_name)
        {
            delete *it; // Liberamos la memoria reservada para el canal
            _channelList.erase(it); // Eliminamos el puntero al canal del vector
            return;
        }
    }
}

bool Server::channelExists(std::string channel_name)
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

Channel*	Server::getChannel(std::string channel_name)
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

void Server::printChannel(std::string channel_name)
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
    std::vector<Client*> clients = channel->getClients();
    for (size_t i = 0; i < clients.size(); i++)
    {
        std::cout << "    - " << clients[i]->getNickname() << std::endl;
    }
}

std::string		Server::getServInfo( void ) const{ return _serverInfo;}


std::string	Server::isOper(Client *client)
{
	for (size_t i = 0; i < _channelList.size(); i++)
	{
		if (_channelList[i]->isOperator(client) == true)
			return "is an IRC operator";
	}
	return "is not an operator";
}

bool	Server::finish()
{
    std::cout << "\nTerminating server...\n";
	for (std::map<int , Client *>::iterator it = this->_clientsList.begin(); it != this->_clientsList.end(); it++)
		this->removeClient(it->second);
    close(getServerSocket()); // cerrar el socket
    return (true); // salir del programa con el codigo de señal
	// for (std::vector<Channel *>::iterator it = _channelList.begin(); it != _channelList.end(); it++)
	// // removeChannel((*it)->getName());
	// {
	// 	delete *it; // Liberamos la memoria reservada para el canal
    //     _channelList.erase(it);
	// }
}

std::ostream		&operator<<( std::ostream & o, Server const & rhs )
{
	o << std::endl << YELLOW << "******\tServer info\t******" << RESET << std::endl;
	o << "Name: " << rhs.getName() << std::endl;
	o << "Password: " << rhs.getPassword() << std::endl;
	o << "Port: " << rhs.getPort() << std::endl;
	o << "Server Socket: " << rhs.getServerSocket() << std::endl;
	o << "Number of clients: " << rhs.getNOfClients() << std::endl;
	o << "State: " << rhs.getServerState() << std::endl;
	o << "Created: " << ctime(rhs.getStartTime()) << std::endl;
	return o;
}
