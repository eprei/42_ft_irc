# include "Includes.hpp"

// TO DO: write copilen's functions

Server::Server(){}

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
	return 0;
}

bool Server::printCorrectUse() const
{
	std::cout << "Correct use of ircserv: ./ircserv <port> <password>" << std::endl;
	std::cout << "<port> must be a number between 6665-6669" << std::endl; // Choix des ports en fonction de l'article https://fr.wikipedia.org/wiki/Internet_Relay_Chat
	return 1;
}

void Server::printHelp() const // TO DO: print all possible commands to be used by the Client in our Server
{

}

void Server::loop(){
	std::cout << "you are in the loop" << std::endl;
}
