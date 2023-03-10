# include "Server.hpp"
# include "Includes.hpp"

// TO DO: write copilen's functions

Server::Server(){
	this->_nOfClients = 4; // TO DELETE; just to test
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
	this->_port = atoi(argv[1]);
	this->_password = argv[2];
	std::cout << "port = " << _port << "\tpass = " << _password << std::endl; // TO DELETE:
	return 0;
}

bool Server::printCorrectUse() const
{
	std::cout << "Correct use of ircserv: ./ircserv <port> <password>" << std::endl;
	std::cout << "<port> must be a number between 6665-6669" << std::endl; // Choix des ports en fonction de l'article https://fr.wikipedia.org/wiki/Internet_Relay_Chat
	return 1;
}

void Server::launchServ(){
//	SOCKET CREATION
	if ((this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		std::cout << "ERROR: socket function error" << std::endl; // TO CONSIDER: We must decide how to deal with this error and consider to throw exceptions or kill the program ???
		exit(EXIT_FAILURE); // TO DO: this EXIT is temporary since we do not have the right to use the EXIT function, we must handle it differently.
	}
//	INITIALIZE THE ADDRESS STRUCTURE
	bzero(&_serverAddress.sin_zero, sizeof(_serverAddress));
	this->_serverAddress.sin_family = AF_INET;
	this->_serverAddress.sin_port = htons(this->_port);
	this->_serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	// bzero(&(_serverAddress.sin_zero), 8);

//	BIND SOCKET WITH A PORT
	if ((bind(_serverSocket, (struct sockaddr *)&_serverAddress, sizeof(_serverAddress))) < 0){
		perror("\nerror found at bind"); // TO CONSIDER: We must decide how to deal with this error and consider to throw exceptions or kill the program ???
		exit(EXIT_FAILURE); // TO DO: this EXIT is temporary since we do not have the right to use the EXIT function, we must handle it differently.
	}
// LISTEN
	if ((listen(_serverSocket, MAX_CONNECTIONS_ON_STANDBY)) < 0){
		perror("\nerror found at listen"); // TO CONSIDER: We must decide how to deal with this error and consider to throw exceptions or kill the program ???
		exit(EXIT_FAILURE); // TO DO: this EXIT is temporary since we do not have the right to use the EXIT function, we must handle it differently.
	}

// SET THE GROUPS OF FD THAT WILL BE CHECKED BY SELECT
	FD_ZERO(&this->_currentSockets);
	FD_SET(this->_serverSocket, &this->_currentSockets);

// START THE LOOP
	while (1)
	{
		// this is to keep safe the information of this->_currentSocket
		// we have to work in a copy (_readySocket) because select is destructive,
		// it overwrites the structure and we lose the previous information
		this->_readySockets = this->_currentSockets;
		if (select(FD_SETSIZE, &this->_readySockets, NULL, NULL, NULL) < 0){
			perror("\nerror found at select"); // TO CONSIDER: We must decide how to deal with this error and consider to throw exceptions or kill the program ???
			exit(EXIT_FAILURE); // TO DO: this EXIT is temporary since we do not have the right to use the EXIT function, we must handle it differently.
		}

		for (int i = 0; i < this->_nOfClients; i++){
			if (FD_ISSET(i, &this->_readySockets)){
				// i it's a fd with data that we can read right now. Two cases are possibles
				if (i == this->_serverSocket){
					// this is a new connection that we can accept
					int addrSize = sizeof(struct sockaddr_in);
					int clientSocketLocal;
					struct sockaddr_in clientAddr; 	// TO CONSIDER: at this point we could copy the clientAddr information
													// into the corresponding client structure
					clientSocketLocal = accept(this->_serverSocket, (struct sockaddr*)&clientAddr, (socklen_t*)&addrSize);
					// TO DO: at this point we could copy the clientSocketLocal into the corresponding client structure
					FD_SET(clientSocketLocal, &this->_currentSockets);
				}
				else {
					// this is an already connected client sending us a message, so we can handle the message
					char *buff[MAX_BUFF];
					if (recv( i, buff, MAX_BUFF, 0) < 0){
						std::cout << "ERROR: bind function error" << std::endl; // TO CONSIDER: We must decide how to deal with this error and consider to throw exceptions or kill the program ???
						exit(EXIT_FAILURE); // TO DO: this EXIT is temporary since we do not have the right to use the EXIT function, we must handle it differently.
					}
					std::cout << "New message received: " << buff << std::endl;
				}
			}
		}
	}
}
