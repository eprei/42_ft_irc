#include "Client.hpp"

// TO DO: write copilen's functions
int Client::_maxId = 0;

Client::Client(Server *s): _nickname(CLIENT_NICKNAME_NOT_SET),
 _username(CLIENT_USERNAME_NOT_SET), _hostname(CLIENT_HOSTNAME_NOT_SET),
 _realname(CLIENT_REALNAME_NOT_SET), _server(s){
	_maxId += 1;
	_id = Client::_maxId;
	_isRegistered = false;
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

void 				Client::setBuf(std::string buf){
	_buf += buf;
	if (_buf.find(END_CHARACTERS) != std::string::npos )
	{
		process_buffer(_buf);
		_buf.clear();
	}
}

void	Client::process_buffer(const std::string& buf)
{
	Message	m;
    char	*token = strtok(const_cast<char*>(buf.c_str()), END_CHARACTERS);

    while (token != NULL)
	{
        std::string command(token);// Convierte token en string
        std::cout << "Comando recibido: " << command << std::endl;
		m = parseMessage(command);
		std::cout << FC(GREEN, "Message parsed =") << std::endl;
		print_message(m);
		execCmd(&m);
        token = strtok(NULL, END_CHARACTERS); // Siguiente token
    }
}

void			Client::execCmd(Message *m){
	std::string acceptableCommands[NUMBER_OF_ACCEPTABLE_COMMANDS] =\
	{ "NICK" , "USER" , "PASS" , "JOIN" , "QUIT" , "LIST" , "PART"\
	, "PRIVMSG" , "PING" , "KICK" , "CAP" , "NOTICE" , "MODE", "PONG" , "WHOIS" }; // ISON ?
	void	(Client::*p[NUMBER_OF_ACCEPTABLE_COMMANDS])(Message *) =\
	{ &Client::nick , &Client::user , &Client::pass , &Client::join, \
	&Client::quit, &Client::list, &Client::part , &Client::privmsg , \
	&Client::ping , &Client::kick , &Client::cap , &Client::notice , &Client::mode, &Client::pong , &Client::whois };

	std::cout << FC(BLUE, ">\texeccmd function executed ") << "by client id: " << _id << "\t<" << RESET << std::endl;
	for (int i = 0; i < NUMBER_OF_ACCEPTABLE_COMMANDS; i++)
	{
		if (acceptableCommands[i].compare(m->command) == 0)
		{
			(this->*p[i])(m);
			return ;
		}
	}
	std::cout << RED << ">\t\tunknow command\t\t\t<" << RESET << std::endl;
}

void			Client::join(Message *m){
	(void)m;
	std::cout << GREEN << ">\tjoin function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::quit(Message *m){
	(void)m;
	std::cout << GREEN << ">\tquit function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::list(Message *m){
	(void)m;
	std::cout << GREEN << ">\tlist function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::part(Message *m){
	(void)m;
	std::cout << GREEN << ">\tpart function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::privmsg(Message *m){
	(void)m;
	std::cout << GREEN << ">\tprivmsg function executed " << RESET <<"by client id: " << _id << "\t<" << std::endl;
}

void			Client::ping(Message *m){
	(void)m;
	std::cout << GREEN << ">\tping function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::kick(Message *m){
	(void)m;
	std::cout << GREEN << ">\tkick function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::cap(Message *m){
	(void)m;
	std::cout << GREEN << ">\tcap function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::notice(Message *m){
	(void)m;
	std::cout << GREEN << ">\tnotice function executed " << RESET <<"by client id: " << _id << "\t<" << std::endl;
}

void			Client::mode(Message *m){
	(void)m;
	std::cout << GREEN << ">\tmode function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

void			Client::pong(Message *m){
	(void)m;
	std::cout << GREEN << ">\tpong function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
}

int					Client::getId( void ) const {return _id;}
std::string			Client::getNickname( void ) const {return _nickname;}
std::string			Client::getUsername( void ) const{return _username;}
std::string			Client::getHostname( void ) const{return _hostname;}
std::time_t			Client::getlastCommunication( void ) const{return _lastCommunication;}
int					Client::getSocket( void ) const{return _socket;}
struct sockaddr_in	Client::getAddress( void ) const{return _address;}
std::string			Client::getBuf( void ) const{return _buf;}
int					Client::getMaxId( void ) const {return _maxId;}

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
