#include "Client.hpp"
#include "Server.hpp"

void			Client::user(Message *m){

	std::cout << GREEN << ">\tuser function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;

	if (m->params[0].size() < 4 || m->params[0].empty() || m->params[1].empty() || m->params[2].empty() || m->params[3].empty())
		send_reply(461, this, _server, "user", "", "", "");
	else
	{
		_username = m->params[0];
		_hostname = m->params[1];
		(void) m->params[2]; // inused parameter. in RFC 1459 is <servername> but In 2812 is <unused>
		_realname = m->params[3];
		std::string msg = formatMsgsUsers(_nickname, _username, getHostname());
		msg.append("USERNAME " + _username + " HOSTNAME " + _hostname + " REALNAME " + _realname +"\r\n");

		std::cout << FC(YELLOW, "Server Reply to be sent:\n") << msg << std::endl;
		if (send(getSocket(), msg.c_str(), msg.length(), 0) < 0)
			perror("SEND FAILED");
	}

}


		this->setNickname(m->params[0]);
		std::string msg = ":"; // formatMsgsUsers(_nickname, _username, getHostname());
		msg.append(_server->getName());
		msg.append(" ");
		msg.append("99");
		msg.append(" ");
		msg.append("NICK " + _nickname + " has succesfully changed his nickname\r\n");
		// msg.append("NICK " + _nickname + "\r\n");

		std::cout << FC(YELLOW, "Server Reply to be sent:\n") << msg << std::endl;
		if (send(getSocket(), msg.c_str(), msg.length(), 0) < 0)
			perror("SEND FAILED");
