# include "Channel.hpp"

// TO DO: write copilen's functions
Channel::Channel(Client &owner, std::string name) :
_oper(&owner), _name(name) 
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
std::vector<Client*> Channel::getClients() const {
	return members;
}

void Channel::addClient(Client* client) {
	members.push_back(client);
}

void Channel::removeClient(Client* client) {
	for (std::vector<Client*>::iterator it = members.begin(); it != members.end(); ++it) {
		if ((*it)->getNickname() == client->getNickname()) {
			members.erase(it);
			return;
		}
	}
}

bool	Channel::hasClient(Client* client) const {
	for (std::vector<Client*>::const_iterator it = members.begin(); it != members.end(); ++it) {
		if (*it == client) {
			return true;
		}
	}
	return false;
}

bool	Channel::isEmpty() const{
	if (members.empty())
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