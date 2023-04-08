#include "Client.hpp"

// TO DO: write copilen's functions
int Client::_maxId = 0;
std::vector<nicksBackup>	Client::_nicksHistory;

Client::Client(Server *s): /*_nickname(CLIENT_NICKNAME_NOT_SET),
 _username(CLIENT_USERNAME_NOT_SET), _hostname(CLIENT_HOSTNAME_NOT_SET),
 _realname(CLIENT_REALNAME_NOT_SET),*/ _server(s){
	_maxId += 1;
	_id = Client::_maxId;
	_isRegistered = false;
	_alreadyWelcomed = false;
	time(&_lastCommunication);
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
void				Client::setIp(std::string ip){_ip = ip;}

void 				Client::setBuf(std::string buf){
	time(&_lastCommunication);
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
        // std::cout << "Comando recibido: " << command << std::endl;
		m = parseMessage(command);
		std::cout << FC(GREEN, "Message parsed =") << std::endl;
		print_message(m);
		execCmd(&m);
        token = strtok(NULL, END_CHARACTERS); // Siguiente token
    }
}

void			Client::execCmd(Message *m){
	std::string acceptableCommands[NUMBER_OF_CMD] =\
	{ "NICK" , "USER" , "PASS" , "JOIN" , "QUIT" , "LIST" , "PART"\
	, "PRIVMSG" , "PING" , "KICK" , "CAP" , "NOTICE" , "MODE", "PONG"\
	, "WHOIS" , "WHOWAS", "TOPIC", "INVITE"};
	void	(Client::*p[NUMBER_OF_CMD])(Message *) =\
	{ &Client::nick , &Client::user , &Client::pass , &Client::join, \
	&Client::quit, &Client::list, &Client::part , &Client::privmsg , \
	&Client::ping , &Client::kick , &Client::cap , &Client::notice , \
	&Client::mode, &Client::pong , &Client::whois , &Client::whowas, \
	&Client::topic, &Client::invite};

	// std::cout << FC(BLUE, ">\texeccmd function executed ") << "by client id: " << _id << "\t<") << std::endl;
	for (int i = 0; i < NUMBER_OF_CMD; i++)
	{
		if (acceptableCommands[i].compare(m->command) == 0)
			return ((this->*p[i])(m));
	}
}

int					Client::getId( void ) const {return _id;}
std::string			Client::getNickname( void ) const {return _nickname;}
std::string			Client::getUsername( void ) const{return _username;}
std::string			Client::getHostname( void ) const{return _hostname;}
std::string			Client::getRealname( void ) const{return _realname;}
int					Client::getSocket( void ) const{return _socket;}
struct sockaddr_in	Client::getAddress( void ) const{return _address;}
std::string			Client::getBuf( void ) const{return _buf;}
int					Client::getMaxId( void ) const {return _maxId;}
std::string			Client::getIp( void ) const{return _ip;}
double 				Client::getIdle( void ) const{
	time_t actual;

	time(&actual);
	return std::difftime(actual, _lastCommunication);
}

std::ostream		&operator<<( std::ostream & o, Client const & rhs )
{
	o << FC(YELLOW, "******\tClient info\t******") << std::endl;
	o << "ID: " << rhs.getId() << std::endl;
	o << "Nickname: " << rhs.getNickname() << std::endl;
	o << "Username: " << rhs.getUsername() << std::endl;
	o << "Hostname: " << rhs.getHostname() << std::endl;
	o << "Last communication: " << rhs.getIdle() << std::endl;
	o << "Client Socket: " << rhs.getSocket() << std::endl;
	// o << "Address: " << rhs.getAddress() << std::endl; TO CONSIDER: if it's usefull to print this infos to debug
	return o;
}

//  Client: Esta clase representaría a cada cliente que se conecta al servidor IRC.
//   Sería responsable de mantener una conexión con el servidor, recibir y enviar mensajes,
//    y unirse o abandonar canales.

std::vector<std::string> Client::subSplitString(const std::string& str, char c) {
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string strSplited;

	while (std::getline(ss, strSplited, c))
		result.push_back(strSplited);
	return result;
}

void	Client::addJoinedChannel(Channel *ch)
{
	_joinedChannels.push_back(ch);
}

void	Client::removeJoinedChannel(Channel *ch)
{
	for (std::vector<Channel*>::iterator it = _joinedChannels.begin(); it != _joinedChannels.end(); ++it)
	{
		if ((*it)->getName() == ch->getName()) 
		{	
			_joinedChannels.erase(it);
			return;
		}
	}
}

// bool	Client::isJoinedChannel(Channel *ch) const
// {
// 	std::string target_name = ch->getName();
// 	for (std::vector<Channel*>::const_iterator it = _joinedChannels.begin(); it != _joinedChannels.end(); ++it)
// 	{
// 		if ((*it)->getName() == client) {
// 			return true;
// 		}
// 	}
// 	return false;
// }

