#include "../srcs/Includes.hpp"

// made by: mpons


#define ERR_NOSUCHSERVER "no existe el servidor"

void			Client::ping(Message *m){
	std::cout << FC(GREEN, ">\tping function executed ") <<"by client id: " << _id << "\t\t<" << std::endl;
	// if (m->params.empty())
		// return (s.numeric_reply(u, ERR_NOORIGIN, NONE, NONE, NONE));
	// else if (m->params.size() <= 1)
	if (m->params.size() <= 1)
	{
		// if (m->params[0] != _hostname)
		// 	return (sendReply(this, ERR_NOSUCHSERVER, m->params[0], "", ""));
		std::string to_send = "PONG " + m->params[0] + END_CHARACTERS;
		sendMsg(to_send);
	}
}
