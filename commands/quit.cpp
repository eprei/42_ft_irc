#include "../srcs/Includes.hpp"

// made by: epresa-c

// TO DO: WRITE THIS FUNCTION CORRECTLY
//		and send messages to the corresponding channel after sendMsgToChannel(m->params[0] if exist) function is implemented

void			Client::quit(Message *m){

	std::cout << GREEN << ">\tquit function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;

	if (m->params[0].size() == 0)
		_server->removeClientFromServer(this, "");
	else
		_server->removeClientFromServer(this, m->params[0]);
	//TO DO: sendToChannel( client_nickname "has quit the channel");
}

