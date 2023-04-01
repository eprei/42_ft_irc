#include "../srcs/Includes.hpp"

// TO DO: Choose a fix client

void			Client::user(Message *m){

	std::cout << GREEN << ">\tuser function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;

	if (m->params[0].size() < 4 || m->params[0].empty() || m->params[1].empty() || m->params[2].empty() || m->params[3].empty())
		send_reply(461, this, _server, "user", "", "", "");
	else
	{
		_username = m->params[0];
		_hostname = m->params[1];
		(void) m->params[2]; // inused parameter. in RFC 1459 is <servername> but In 2812 is <unused>
		// RFC 1459 (usado por irssi)  ===> Command: USER   /     Parameters: <username> <hostname> <servername> <realname>
		// RFC 2812 (usado por getIRC)  ===> Command: USER   /    Parameters: <user> <mode> <unused> <realname>
		_realname = m->params[3];
		std::string msg = formatMsgsUsers(_nickname, _username, getHostname());
		msg.append( "Nickname: " + _nickname + "\nUsername: " + _username + "\nHostname: " + _hostname + "\nReal name: " + _realname + "\nConnected to: " + _server->getName() + "\r\n");

		std::cout << FC(YELLOW, "Server Reply to be sent:\n") << msg << std::endl;
		if (send(getSocket(), msg.c_str(), msg.length(), 0) < 0)
			perror("SEND FAILED");
	}
}
