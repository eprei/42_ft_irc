# include "Channel.hpp"

// TO DO: write copilen's functions
Channel::Channel(Client &owner, std::string name) :
_oper(&owner), _name(name),
_modes("+nt")
// _modes("+i")
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
	for (std::vector<Client*>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
		if (*it == client) {
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
