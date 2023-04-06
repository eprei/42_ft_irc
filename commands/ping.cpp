#include "../srcs/Includes.hpp"

// made by: mpons


#define ERR_NOSUCHSERVER "no existe el servidor"

void			Client::ping(Message *m){
	std::cout << GREEN << ">\tping function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;
	// if (m->params.empty())
		// return (s.numeric_reply(u, ERR_NOORIGIN, NONE, NONE, NONE));
	// else if (m->params.size() <= 1)
	if (m->params.size() <= 1)
	{
		// if (m->params[0] != _hostname)
		// 	return (send_reply(this, ERR_NOSUCHSERVER, m->params[0], "", ""));
		std::string to_send = "PONG " + m->params[0] + END_CHARACTERS;
		send(getSocket(), to_send.c_str(), to_send.size(), 0);
		// std::cout << std::endl << *this << std::endl;
	}
}
