#include "Client.hpp"

//  Client: Esta clase representaría a cada cliente que se conecta al servidor IRC.
//   Sería responsable de mantener una conexión con el servidor, recibir y enviar mensajes,
//    y unirse o abandonar canales.

// TO DO: write copilen's functions
int Client::_maxId = 0;
std::vector<nicksBackup>	Client::_nicksHistory;

Client::Client(Server *s): _server(s), _pass(PASS_NOT_YET_ENTERED){
	_maxId += 1;
	_id = Client::_maxId;
	_isRegistered = false;
	_alreadyWelcomed = false;
	_quiting = false;
	time(&_lastCommunication);
}

Client::Client(Client &other){ *this = other;}

Client &Client::operator=(Client &other){
	(void) other;
	return (*this);
}

Client::~Client(){}

// SETTERS SETTERS SETTERS SETTERS SETTERS SETTERS SETTERS SETTERS

void				Client::setNickname(std::string nickname){_nickname = nickname;}
void				Client::setUsername(std::string username){_username = username;}
void				Client::setHostname(std::string hostname){_hostname = hostname;}
void				Client::setLastCommunication(std::time_t lastCommunication){_lastCommunication = lastCommunication;}
void 				Client::setSocket(int socket){_socket = socket;}
void 				Client::setAddress(struct sockaddr_in address){_address = address;}
void				Client::setIp(std::string ip){_ip = ip;}

// GETTERS GETTERS GETTERS GETTERS GETTERS GETTERS GETTERS GETTERS

bool				Client::isQuiting() { return (_quiting);}
int					Client::getId() const {return _id;}
std::string			Client::getNickname() const {return _nickname;}
std::string			Client::getUsername() const {return _username;}
std::string			Client::getHostname() const {return _hostname;}
std::string			Client::getRealname() const {return _realname;}
int					Client::getSocket() const {return _socket;}
struct sockaddr_in	Client::getAddress() const {return _address;}
std::string			Client::getBuf() const {return _buf;}
int					Client::getMaxId() const {return _maxId;}
std::string			Client::getIp() const {return _ip;}
int					Client::getPass() const {return _pass;}

double 				Client::getIdle() const {
	time_t actual;

	time(&actual);
	return std::difftime(actual, _lastCommunication);
}

// BUFFER BUFFER BUFFER BUFFER BUFFER BUFFER BUFFER BUFFER BUFFER BUFFER

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

	if ( strchr(token, ' ') == NULL )
		return;
    while (token != NULL)
	{
        std::string command(token);// Convierte token en string
        // std::cout << "Comando recibido: " << command << std::endl;
		m = parseMessage(command);
		std::cout << FC(GREEN, "Message parsed =") << std::endl;
		print_message(m);
		if (this->_isRegistered == false && ( m.command != "CAP" && m.command != "PASS" ))
		{
			std::cout << "Client " << this->_id << " has not yet entered the correct password" << std::endl;
			return (sendReply(464, "", "", "", ""));
		}
		execCmd(&m);
        token = strtok(NULL, END_CHARACTERS); // Siguiente token
    }
}

void			Client::execCmd(Message *m){
	std::string acceptableCommands[NUMBER_OF_CMD] = \
	{ "NICK" , "USER" , "PASS" , "JOIN" , "QUIT" , "LIST" , "NAMES" \
	, "PART" , "PRIVMSG" , "PING" , "KICK" , "NOTICE" , "MODE", "PONG"\
	, "WHOIS" , "WHOWAS", "TOPIC", "INVITE"};
	void	(Client::*p[NUMBER_OF_CMD])(Message *) = \
	{ &Client::nick , &Client::user , &Client::pass , &Client::join, \
	&Client::quit, &Client::list, &Client::names, &Client::part , \
	&Client::privmsg , &Client::ping , &Client::kick , &Client::notice , \
	&Client::mode, &Client::pong , &Client::whois , &Client::whowas, \
	&Client::topic, &Client::invite};

	for (int i = 0; i < NUMBER_OF_CMD; i++)
	{
		if (acceptableCommands[i].compare(m->command) == 0)
			return ((this->*p[i])(m));
	}
}

std::vector<std::string> Client::subSplitString(const std::string& str, char c) {
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string strSplited;

	while (std::getline(ss, strSplited, c))
		result.push_back(strSplited);
	return result;
}

// JOINED CHANNELS JOINED CHANNELS JOINED CHANNELS JOINED CHANNELS JOINED CHANNELS

void	Client::addJoinedChannel(Channel *ch)
{
	_joinedChannels.push_back(ch);
}

void	Client::removeJoinedChannel(Channel *ch)
{
	std::vector<Channel*>::iterator it = _joinedChannels.begin();
	for ( ; it != _joinedChannels.end(); ++it)
	{
		if ((*it)->getName() == ch->getName())
		{
			_joinedChannels.erase(it);
			return;
		}
	}
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
