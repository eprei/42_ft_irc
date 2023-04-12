# include "Channel.hpp"

// TO DO: write copilen's functions?
//	  i - invite-only channel flag;
//    t - topic settable by channel operator only flag;
//    n - no messages to channel from clients on the outside;
Channel::Channel(Client &owner, std::string name) :
_oper(&owner), _name(name), _modes("+nt")
{}

Channel::Channel(Channel &other){ *this = other;}

Channel &Channel::operator=(Channel &other){
	(void) other;
	return (*this);
}

Channel::~Channel(){}

std::string	Channel::getName() const
{
	return _name;
}

//Clients
std::vector<Client*> Channel::getMembers() const {
	return _members;
}

std::string	Channel::getMembersNicks()
{ 
	std::string all_nicks;
	for (std::vector<Client *>::iterator it = _members.begin(); it != _members.end(); ++it)
		all_nicks += (*it)->getNickname() + " ";
	return all_nicks;
}

void Channel::addClient(Client* client) {
	_members.push_back(client);
}

void Channel::removeClient(Client* client) {
	for (std::vector<Client*>::iterator it = _members.begin(); it != _members.end(); ++it) {
		if ((*it)->getNickname() == client->getNickname()) {
			_members.erase(it);
			return;
		}
	}
}

bool	Channel::hasClient(Client* client) const {
	std::string client_nick = client->getNickname();
	std::vector<Client*>::const_iterator it = _members.begin();
	for ( ; it != _members.end(); ++it) {
		if ((*it)->getNickname() == client_nick) {
			return true;
		}
	}
	return false;
}

bool	Channel::isEmpty() const{
	if (_members.empty())
		return true;
	return false;
}

bool	Channel::isOperator(Client *client) const
{
	if (_oper->getNickname() == client->getNickname())
		return (true);
	return (false);
}

//TOPIC
void	Channel::setTopic(std::string topic) {
	this->_topic = topic;
}
std::string	Channel::getTopic() const {
	return _topic;
}

std::string	Channel::getModes() const
{
	return _modes;
}

std::string Channel::setModes(std::string set)
{
    std::string valid_modes = "nti";
    std::string seted_modes;
    for (std::string::iterator it = (set.begin() + 1); it != set.end(); ++it)
	{
        if (valid_modes.find(*it) != std::string::npos)//el char a modificar es valido
		{
            if (_modes.find(*it) == std::string::npos && set[0] == '+')//no esta ya agregado
			{
            	_modes.push_back(*it);
	           	seted_modes.push_back(*it);
			}
			if (_modes.find(*it) != std::string::npos && set[0] == '-')//si esta ya agregado
			{
			    _modes.erase(_modes.find(*it), 1);
	           	seted_modes.push_back(*it);
			}
        }
        else  //no valido
            return (seted_modes + "_" + *it);
    }
    return seted_modes;
}

bool	Channel::hasModes(std::string m) const
{
	for (std::string::iterator it = m.begin(); it != m.end(); ++it)
	{
		if (_modes.find(*it) == std::string::npos)//no encontramos el char
			return (false);
	}
	return (true);
}

bool	Channel::isInvited(Client *client) const
{
	for (std::vector<Client*>::const_iterator it = _invited.begin(); it != _invited.end(); ++it)
	{
		std::cout << *(*it) << std::endl; 
		if ((*it)->getId() == client->getId() &&\
		(*it)->getUsername() == client->getUsername() &&\
		(*it)->getHostname() == client->getHostname())
			return true;
	}
	return false;
}

void Channel::addInvited(Client* client) {
	_invited.push_back(client);
}

std::ostream	&operator<<(std::ostream & o, Channel const & rhs )
{
	o << FC(GREEN, "******\tChannel info\t******") << std::endl;
	o << "Name: " << rhs.getName() << std::endl;
	o << "Modes: " << rhs.getModes() << std::endl;
	if (!rhs.getTopic().empty())
		o << "Topic: " << rhs.getTopic() << std::endl;
	return o;
}
