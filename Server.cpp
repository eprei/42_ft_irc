# include "Server.hpp"
# include "Includes.hpp"

// TO DO: write copilen's functions

Server::Server(): _name("42_IRC"), _nOfClients(0), _serverState(IS_ON){
}

Server::Server(Server &other){ *this = other;}

Server &Server::operator=(Server &other) // TO DO: Add to this function all the new parameters that are added to the Server class
{
	this->_password = other._password;
	this->_port = other._port;
	this->_clientsList = other._clientsList;
	return (*this);
}

Server::~Server(){}

bool Server::checkArgs(int argc, char **argv){
	if (argc != 3 || !(DEFAULT_MIN_PORT <= atoi(argv[1]) && atoi(argv[1]) <= DEFAULT_MAX_PORT))
		return printCorrectUse();
	_port = atoi(argv[1]);
	_password = argv[2];
	// std::cout << "port = " << _port << "\tpass = " << _password << std::endl; // TO DELETE:
	return EXIT_SUCCESS;
}

bool Server::printCorrectUse() const
{
	std::cout << "Correct use of ircserv: ./ircserv <port> <password>" << std::endl;
	std::cout << "<port> must be a number between 6665-6669" << std::endl; // Choix des ports en fonction de l'article https://fr.wikipedia.org/wiki/Internet_Relay_Chat
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
//	SOCKET CREATION
	if ((_serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		std::cout << "ERROR: socket function error" << std::endl; // TO CONSIDER: We must decide how to deal with this error and consider to throw exceptions or kill the program ???
		return (EXIT_FAILURE); // TO DO: this EXIT is temporary since we do not have the right to use the EXIT function, we must handle it differently.
	}

//	INITIALIZE THE SERVER'S ADDRESS STRUCTURE
	bzero(&_serverAddress.sin_zero, sizeof(_serverAddress));
	this->_serverAddress.sin_family = AF_INET;
	this->_serverAddress.sin_port = htons(this->_port);
	this->_serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	// bzero(&(_serverAddress.sin_zero), 8);

//	BIND SOCKET WITH A PORT
	if ((bind(_serverSocket, (struct sockaddr *)&_serverAddress, sizeof(_serverAddress))) < 0){
		perror("\nerror found at bind"); // TO CONSIDER: We must decide how to deal with this error and consider to throw exceptions or kill the program ???
		return (EXIT_FAILURE); // TO DO: this EXIT is temporary since we do not have the right to use the EXIT function, we must handle it differently.
	}
// LISTEN
	if ((listen(_serverSocket, MAX_CONNECTIONS_ON_STANDBY)) < 0){
		perror("\nerror found at listen"); // TO CONSIDER: We must decide how to deal with this error and consider to throw exceptions or kill the program ???
		return (EXIT_FAILURE); // TO DO: this EXIT is temporary since we do not have the right to use the EXIT function, we must handle it differently.
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
	struct sockaddr_in clientAddr; 	// TO CONSIDER: at this point we could copy the clientAddr information into the corresponding client structure
	Client *neo = new Client;

	if ((clientSocketLocal = accept(this->_serverSocket, (struct sockaddr*)&clientAddr, (socklen_t*)&addrSize)) < 0){
		perror("\nerror found at accept"); // TO CONSIDER: We must decide how to deal with this error and consider to throw exceptions or kill the program ???
		delete neo;
		return ;
	}
	neo->setSocket(clientSocketLocal);
	neo->setAddress(clientAddr);
	_clientsList.insert(std::pair<int , Client *>(neo->getSocket(), neo));
	FD_SET(clientSocketLocal, &_currentSockets);
	std::cout << GREEN << "++++++\tClient " << neo->getId() << " added\t++++++\n" << RESET << *neo << std::endl;
	// FD_CLEAR(i, &_currentSockets); TO USE IN THE FUTURE: when we delete a user
	// if (FD_ISSET(i, &_readySockets)){
}

bool Server::serverLoop(){
	// TO DO: Handle the signals and set _serverState to IS_OFF when a unix signal is reciveded
	while (_serverState == IS_ON)
	{
		// this is to keep safe the information of this->_currentSocket
		// we have to work in a copy (_readySocket) because select is destructive,
		// it overwrites the structure and we lose the previous information
		_readySockets = _currentSockets;
		if (select(FD_SETSIZE, &_readySockets, NULL, NULL, NULL) < 0){
			// (errno == EINTR) To verify if we control errno or not because if we do we could go against what is requested in the evaluation
			// EINTR = A signal was delivered before the time limit expired and before any of the selected events occurred
			perror("\nerror found at select"); // TO CONSIDER: We must decide how to deal with this error and consider to throw exceptions or kill the program ???
			return (EXIT_FAILURE); // TO DO: this EXIT is temporary since we do not have the right to use the EXIT function, we must handle it differently.
		}
		for (int i = 0; i < FD_SETSIZE; i++) // TO OPTIMIZE: change FD_SETSIZE by the number or users to reduce the amount of iterations
		{
			if (FD_ISSET(i, &_readySockets)){
				// i it's a fd with data that we can read right now. Two cases are possibles
				if (i == this->_serverSocket){
					// this is a new connection that we can accept
					addNewClient();
				}
				else {
					// this is an already connected client sending us a message, so we can handle the message
					messageHandling(i);
				}
			}
		}
		usleep(600);
	}
	return (EXIT_SUCCESS);
}

void			Server::messageHandling(int fd){
	// TO DO:
	char buff[MAX_BUFF];
	if (recv( fd, buff, MAX_BUFF, 0) < 0){
		std::cout << "ERROR: recv function error" << std::endl; // TO CONSIDER: We must decide how to deal with this error and consider to throw exceptions or kill the program ???
		// return (EXIT_FAILURE); // TO DO: this EXIT is temporary since we do not have the right to use the EXIT function, we must handle it differently.
	}
	_clientsList.at(fd)->setBuf(buff);
	std::cout << GREEN << "message handled: " << RESET << _clientsList.at(fd)->getBuf() << std::endl;
	// TO DEVELOP: Parsing&Excecute();
}

std::string		Server::getName( void ) const{return _name;}

std::string		Server::getPassword( void ) const{return _password;}

int				Server::getPort( void ) const{return _port;}

int				Server::getServerSocket( void ) const{return _serverSocket;}

int				Server::getNOfClients( void ) const{return _nOfClients;}

std::string		Server::getServerState( void ) const{return _serverState;}


std::ostream		&operator<<( std::ostream & o, Server const & rhs )
{
	o << std::endl << YELLOW << "******\tServer info\t******" << RESET << std::endl;
	o << "Name: " << rhs.getName() << std::endl;
	o << "Password: " << rhs.getPassword() << std::endl;
	o << "Port: " << rhs.getPort() << std::endl;
	o << "Server Socket: " << rhs.getServerSocket() << std::endl;
	o << "Number of clients: " << rhs.getNOfClients() << std::endl;
	o << "State: " << rhs.getServerState() << std::endl;
	return o;
}
