#include "Client.hpp"
#include "Includes.hpp"

// TO DO: write copilen's functions
int Client::_maxId = 0;

Client::Client(): _nickname(CLIENT_NICKNAME_NOT_SET), _username(CLIENT_USERNAME_NOT_SET), _hostname(CLIENT_HOSTNAME_NOT_SET){
	_maxId += 1;
	_id = Client::_maxId;
}

Client::Client(Client &other){ *this = other;}

Client &Client::operator=(Client &other){
	(void) other;
	return (*this);
}

Client::~Client(){
	_maxId -= 1;
}

void				Client::setNickname(std::string nickname){_nickname = nickname;}
void				Client::setUsername(std::string username){_username = username;}
void				Client::setHostname(std::string hostname){_hostname = hostname;}
void				Client::setLastCommunication(std::time_t lastCommunication){_lastCommunication = lastCommunication;}
void 				Client::setSocket(int socket){_socket = socket;}
void 				Client::setAddress(struct sockaddr_in address){_address = address;}
void 				Client::setBuf(std::string buf){_buf = buf;}

void 				Client::setBuf(std::string buf){
	_buf += buf;
	// std::cout << YELLOW << "The client " << this->_id << " has recived a new bufferline: " << RESET << _buf << std::endl;
	if (_buf.find(END_CHARACTERS) != std::string::npos )
	{
		_buf = _buf.substr(0, _buf.find(END_CHARACTERS));
		std::cout << GREEN << "The client " << RESET << this->_id << " has detected an endline" << std::endl;
		parsing();
		execCmd();
		_buf.clear();
	}
}

void				Client::parsing( void ){
	std::cout << BLUE << ">\tparsing function executed " << RESET <<"by client id: " << _id << "\t<" << RESET << std::endl;
}

void			Client::execCmd(){
	std::string acceptableCommands[NUMBER_OF_ACCEPTABLE_COMMANDS] = { "NICK" , "USER" , "PASS" , \
	 "JOIN" , "QUIT" , "LIST" , "PART" , "PRIVMSG" , "PING" , "KICK" , "CAP" , "NOTICE" , "MODE"}; // ISON ?
	void	(Client::*p[NUMBER_OF_ACCEPTABLE_COMMANDS])(void) = { &Client::nick , &Client::user , &Client::pass , &Client::join, \
	&Client::quit, &Client::list, &Client::part , &Client::privmsg , &Client::ping , &Client::kick , &Client::cap , &Client::notice , &Client::mode};

	std::cout << BLUE << ">\texeccmd function executed " << RESET <<"by client id: " << _id << "\t<" << RESET << std::endl;
	for (int i = 0; i < NUMBER_OF_ACCEPTABLE_COMMANDS; i++)
	{
		if (acceptableCommands[i].compare(_buf) == 0)
		{
			(this->*p[i])();
			return ;
		}
	}
	std::cout << RED << ">\t\tunknow command\t\t\t<" << RESET << std::endl;

}


void			Client::nick(){
	std::cout << GREEN << ">\tnick function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::user(){
	std::cout << GREEN << ">\tuser function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::pass(){
	std::cout << GREEN << ">\tpass function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::join(){
	std::cout << GREEN << ">\tjoin function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::quit(){
	std::cout << GREEN << ">\tquit function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::list(){
	std::cout << GREEN << ">\tlist function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::part(){
	std::cout << GREEN << ">\tpart function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::privmsg(){
	std::cout << GREEN << ">\tprivmsg function executed " << RESET <<"by client id: " << _id << "\t<" << std::endl;
}

void			Client::ping(){
	std::cout << GREEN << ">\tping function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::kick(){
	std::cout << GREEN << ">\tkick function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::cap(){
	std::cout << GREEN << ">\tcap function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::notice(){
	std::cout << GREEN << ">\tnotice function executed " << RESET <<"by client id: " << _id << "\t<" << std::endl;
}

void			Client::mode(){
	std::cout << GREEN << ">\tmode function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

int					Client::getId( void ) const {return _id;}
std::string			Client::getNickname( void ) const {return _nickname;}
std::string			Client::getUsername( void ) const{return _username;}
std::string			Client::getHostname( void ) const{return _hostname;}
std::time_t			Client::getlastCommunication( void ) const{return _lastCommunication;}
int					Client::getSocket( void ) const{return _socket;}
struct sockaddr_in	Client::getAddress( void ) const{return _address;}
std::string			Client::getBuf( void ) const{return _buf;}

std::ostream		&operator<<( std::ostream & o, Client const & rhs )
{
	o << FC(YELLOW, "******\tClient info\t******") << std::endl;
	o << "ID: " << rhs.getId() << std::endl;
	o << "Nickname: " << rhs.getNickname() << std::endl;
	o << "Username: " << rhs.getUsername() << std::endl;
	o << "Hostname: " << rhs.getHostname() << std::endl;
	o << "Last communication: " << rhs.getlastCommunication() << std::endl;
	o << "Client Socket: " << rhs.getSocket() << std::endl;
	// o << "Address: " << rhs.getAddress() << std::endl; TO CONSIDER: if it's usefull to print this infos to debug
	return o;
}

//  Client: Esta clase representaría a cada cliente que se conecta al servidor IRC.
//   Sería responsable de mantener una conexión con el servidor, recibir y enviar mensajes,
//    y unirse o abandonar canales.
