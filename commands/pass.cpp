#include "../srcs/Includes.hpp"

// made by: mpons
// Numeric Replies: ERR_NEEDMOREPARAMS ERR_ALREADYREGISTRED
// Example: PASS secretpasswordhere

// we can simplifie this welcome message
void	Client::welcome()
{
	send_reply(1, this, _server, getNickname(), getUsername(), getHostname(), "");
	send_reply(2, this, _server, _server->getName(), "1.0", "", "");
	send_reply(3, this, _server, ctime(_server->getStartTime()), "", "", "");
	// send_reply(4, this, _server, _server->getName(), "1.0", "usermode Hacer", "channelModes Hacer");
}

void	Client::pass(Message *m)
{
	std::cout << GREEN << ">\tpass function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
	if (_isRegistered)
	{
		send_reply(462, this, _server, "", "", "", "");
		return;
	}
	_hostname = _ip;
	_hostname += ".hosted-by-42lausanne.ch";
	if (m->params.empty()) {
		send_reply(461, this, _server, m->command, "", "", "");
		return;
	}
	else if (!m->params[0].compare(_server->getPassword()))
	{
		_isRegistered = true;
		// welcome();
		// if (_nickname.compare(CLIENT_NICKNAME_NOT_SET) || _username.compare(CLIENT_USERNAME_NOT_SET))
	}
	else //wrong pass
	{
		std::cout << BOLDCYAN << "Realpass = "<< _server->getPassword().c_str() << RESET << std::endl;
		send_reply(464, this, _server, "", "", "", "");
		return;
	}
}
