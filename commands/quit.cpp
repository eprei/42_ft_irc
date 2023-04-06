#include "../srcs/Includes.hpp"

// made by: epresa-c

// TO DO: send messages to the corresponding channel after sendMsgToChannel() function is implemented

void			Client::quit(Message *m){

	std::cout << GREEN << ">\tquit function executed " << RESET <<"by client id: " << _id << "\t\t<" << std::endl;

	if (m->params[0].size() == 0)
	{
		_server->removeClientFromServer(this, "");
		//TO DO: sendToChannel( client_nickname "has quit the channel");
	}
	else
	{
		_server->removeClientFromServer(this, "");
		//TO DO: sendToChannel( client_nickname + m->params[0] + m->params[1] ... etc );
		//TO DO: sendToChannel( client_nickname "has quit the channel");
	}
}

