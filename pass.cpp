#include "Client.hpp"
#include "Server.hpp"

// Numeric Replies: ERR_NEEDMOREPARAMS ERR_ALREADYREGISTRED
// Example: PASS secretpasswordhere
// void Client::pass(std::vector<std::string> args) {
void	Client::pass(Message *m)
{
	(void)m;
	std::cout << GREEN << ">\tpass function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
	// if (m->params > 1)
	if (_isRegistered)
	{
		send_reply(462, this, _server, "", "", "", "");
		return;
	}

	if (m->params.empty()) {
		send_reply(461, this, _server, m->command, "", "", "");
		return;
	}
	if (m->params[0].compare(_server->getPassword()))
	{
		std::cout << BOLDCYAN << "Realpass = "<< _server->getPassword().c_str() << RESET << std::endl;
		send_reply(464, this, _server, "", "", "", "");
		return;
	}
	if (!_nickname.empty() && !_username.empty())
	{
		_isRegistered = true;
		send_reply(1, this, _server, getNickname(), getUsername(), getHostname(), "");
		send_reply(2, this, _server, _server->getName(), "1.0", "", "");
		send_reply(3, this, _server, "", "", "", "");
		send_reply(4, this, _server, _server->getName(), "1.0", "usermode Hacer", "channelModes Hacer");
	}
}
