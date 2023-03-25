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
void				Client::setOperator(bool isOperator){_operator = isOperator;}
void				Client::setLastCommunication(std::time_t lastCommunication){_lastCommunication = lastCommunication;}
void 				Client::setSocket(int socket){_socket = socket;}
void 				Client::setAddress(struct sockaddr_in address){_address = address;}
void 				Client::setBuf(std::string buf){_buf = buf;}
int					Client::getId( void ) const {return _id;}
std::string			Client::getNickname( void ) const {return _nickname;}
std::string			Client::getUsername( void ) const{return _username;}
std::string			Client::getHostname( void ) const{return _hostname;}
bool				Client::getOperator( void ) const{return _operator;}
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
	o << std::boolalpha << "Is Operator: " << rhs.getOperator() << std::endl;
	o << "Last communication: " << rhs.getlastCommunication() << std::endl;
	o << "Client Socket: " << rhs.getSocket() << std::endl;
	// o << "Address: " << rhs.getAddress() << std::endl; TO CONSIDER: if it's usefull to print this infos to debug
	return o;
}

//  Client: Esta clase representaría a cada cliente que se conecta al servidor IRC.
//   Sería responsable de mantener una conexión con el servidor, recibir y enviar mensajes,
//    y unirse o abandonar canales.
