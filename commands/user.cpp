#include "../srcs/Includes.hpp"

// made by: epresa-c
// _username = m->params[0]; // doing it this way generates problems since
//  several users connected from the same irsssi would have the same
// _username and it could be confusing for the evaluator
// therefore I chose to do it as in the following line
void			Client::user(Message *m)
{
	std::cout << FC(GREEN, ">\tuser function executed ") <<"by client id: " << _id << "\t\t<" << std::endl;
	std::string user = "USER";
	_username = m->params[0];
	(void) m->params[1];
	_hostname = _ip;
	_hostname += ".hosted-by-42lausanne.ch";
	if (m->params.size() > 1)
		_realname = m->params[3];
	else
		_realname = m->params[0];
	addCommandToRegister(user);
}
	// std::string msg = formatMsgsUsers();
	// msg.append( "Nickname: " + _nickname + "\nUsername: " + _username + "\nHostname: " + _hostname + "\nReal name: " + _realname + "\nConnected to: " + _server->getName() + END_CHARACTERS);
	// sendMsg(msg);
	// if (_isRegistered == true)
		// welcome();
