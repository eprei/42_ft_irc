#include "../srcs/Includes.hpp"

// made by: epresa-c

void			Client::user(Message *m){

	std::cout << GREEN << ">\tuser function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;

	_username = m->params[0];
	(void) m->params[1];
	_hostname = _ip;
	_hostname += ".hosted-by-42lausanne.ch";
	_realname = m->params[3];
	std::string msg = formatMsgsUsers(_nickname, _username, getHostname());
	msg.append( "Nickname: " + _nickname + "\nUsername: " + _username + "\nHostname: " + _hostname + "\nReal name: " + _realname + "\nConnected to: " + _server->getName() + END_CHARACTERS);
	std::cout << FC(YELLOW, "Server Reply to be sent:\n") << msg << std::endl;
	if (send(getSocket(), msg.c_str(), msg.length(), 0) < 0)
		perror("SEND FAILED");
	// if (_isRegistered == true)
		// welcome();
}
