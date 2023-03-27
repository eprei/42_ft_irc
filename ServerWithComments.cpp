# include "Server.hpp"
# include "Includes.hpp"

// TO DO: write copilen's functions

Server::Server(): _name("42_IRC"), _nOfClients(0), _serverState(IS_ON){
	// TO DO: print a welcome message
}

Server::Server(Server &other){ *this = other;}

Server &Server::operator=(Server &other) // TO DO: Add to this function all the new parameters that are added to the Server class
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
	struct sockaddr_in clientAddr;
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
	std::cout << GREEN << "++++++\tClient " << neo->getId() << " added\t++++++\n" << RESET << *neo;
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
		for (int SocketNumber = 0; SocketNumber < FD_SETSIZE; SocketNumber++) // TO OPTIMIZE: change FD_SETSIZE by the number or users to reduce the amount of iterations
		{
			if (FD_ISSET(SocketNumber, &_readySockets)){
				// i it's a fd with data that we can read right now. Two cases are possibles
				if (SocketNumber == _serverSocket){
					// this is a new connection that we can accept
					std::cout << YELLOW << "\n_\tnew conection detected\t_" << RESET << std::endl;
					addNewClient();
				}
				else {
					// this is an already connected client sending us a message, so we can handle the message
					messageHandling(SocketNumber);
				}
			}
		}
		usleep(600);
	}
	return (EXIT_SUCCESS);
}

void	Server::messageHandling(int userSocketNumber){
	ssize_t  numOfBytesReceived;

	bzero(_buf, MAX_BUFF);
	numOfBytesReceived = recv( userSocketNumber, _buf, MAX_BUFF, 0);
	if (numOfBytesReceived < 0){
		std::cout << "ERROR: recv function error" << std::endl; // TO CONSIDER: We must decide how to deal with this error and consider to throw exceptions or kill the program ???
		// return (EXIT_FAILURE); // TO DO: this EXIT is temporary since we do not have the right to use the EXIT function, we must handle it differently.
	}
	std::cout << YELLOW << "\n>\tmessage recived: " << RESET << _buf << YELLOW << "\t\t<" << RESET << std::endl; // TO DELETE: just to debug
	parsing(numOfBytesReceived);
	execCmd();
}

void			Server::parsing(int numOfBytesReceived){
	(void) numOfBytesReceived;
	std::cout << BLUE << ">\tparsing function called\t\t<" << RESET << std::endl;
}

void			Server::execCmd(){
	std::string acceptableCommands[NUMBER_OF_ACCEPTABLE_COMMANDS] = { "nick" , "user" , "pass" , \
	 "join" , "quit" , "list" , "part" , "privmsg" , "ping" , "kick" , "cap" , "notice"}; // MODE & ISON ?
	void	(Server::*p[NUMBER_OF_ACCEPTABLE_COMMANDS])(void) = { &Server::nick , &Server::user , &Server::pass , &Server::join, \
	&Server::quit , &Server::list , &Server::part , &Server::privmsg , &Server::ping , &Server::kick , &Server::cap , &Server::notice };

	std::cout << BLUE << ">\texeccmd function called\t\t<" << RESET << std::endl;

	for (int i = 0; i < NUMBER_OF_ACCEPTABLE_COMMANDS; i++)
	{
		if (acceptableCommands[i].compare(_buf) == 0)
		{
			(this->*p[i])();
			return ;
		}
	}
	std::cout << RED << ">\tunknow command\t\t\t<" << RESET << std::endl;

}


void			Server::nick(){
	std::cout << GREEN << ">\tnick " << RESET << "function executed\t\t" << GREEN << "<" << RESET << std::endl;
}

void			Server::user(){
	std::cout << GREEN << ">\tuser " << RESET << "function executed\t\t" << GREEN << "<" << RESET << std::endl;
}

void			Server::pass(){
	std::cout << GREEN << ">\tpass " << RESET << "function executed\t\t" << GREEN << "<" << RESET << std::endl;
}

void			Server::join(){
	std::cout << GREEN << ">\tjoin " << RESET << "function executed\t\t" << GREEN << "<" << RESET << std::endl;
}

void			Server::quit(){
	std::cout << GREEN << ">\tquit " << RESET << "function executed\t\t" << GREEN << "<" << RESET << std::endl;
}

void			Server::list(){
	std::cout << GREEN << ">\tlist " << RESET << "function executed\t\t" << GREEN << "<" << RESET << std::endl;
}

void			Server::part(){
	std::cout << GREEN << ">\tpart " << RESET << "function executed\t\t" << GREEN << "<" << RESET << std::endl;
}

void			Server::privmsg(){
	std::cout << GREEN << ">\tprivmsg " << RESET << "function executed\t" << GREEN << "<" << RESET << std::endl;
}

void			Server::ping(){
	std::cout << GREEN << ">\tping " << RESET << "function executed\t\t" << GREEN << "<" << RESET << std::endl;
}

void			Server::kick(){
	std::cout << GREEN << ">\tkick " << RESET << "function executed\t\t" << GREEN << "<" << RESET << std::endl;
}

void			Server::cap(){
	std::cout << GREEN << ">\tcap " << RESET << "function executed\t\t" << GREEN << "<" << RESET << std::endl;
}

void			Server::notice(){
	std::cout << GREEN << ">\tnotice " << RESET << "function executed\t" << GREEN << "<" << RESET << std::endl;
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



:servername 001 yournick :Welcome to the Internet Relay Network yournick!user@host


// class Server {
// private:
//   int port;
//   int server_fd;
//   std::vector<Client*> clients;
//   std::vector<std::string> channels;
// public:
//   Server(int port);
//   void start();
//   void handle_new_connection();
//   void handle_client_request(Client* client);
//   void remove_client(Client* client);
//   void broadcast_message(std::string message);
//   void send_message_to_client(Client* client, std::string message);
//   void create_channel(std::string channel_name);
//   void add_client_to_channel(Client* client, std::string channel_name);
//   void remove_client_from_channel(Client* client, std::string channel_name);
//   bool channel_exists(std::string channel_name);
// };

inline void Server::numeric_reply(Client *c, std::string code, std::string arg1, std::string arg2, std::string arg3) 
{
	std::string txt;
	char *ptr;
	txt.append(":");
	txt.append(hostname);
	txt.append(" ");
	txt.append(code);
	txt.append(" ");
	txt.append(u->getNickName()); 
	txt.append(" ");
	txt.append(choose_msg(std::strtol(code.c_str(), &ptr, 10), u, arg1, arg2, arg3));
	txt.append("\r\n");

	out(FG2("Server Reply to be sent:") << code);
	out(txt.c_str());
	if (send(u->socket_descriptor, txt.c_str(), txt.length(), 0) < 0)
	{
		perror("SEND FAILED");
	}
}