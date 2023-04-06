#include "../srcs/Includes.hpp"

// made by: epresa-c
// modified by :mpons
// TO DO: send messages to the corresponding channel after sendMsgToChannel() function is implemented
void	Client::leaveAll(std::string cmd, std::string part_msg)
{
	std::string msg = formatMsgsUsers();
	
	for (std::vector<Channel *>::iterator it = _joinedChannels.begin() ; it != _joinedChannels.end(); it++)
	{
		std::string ch_name = (*it)->getName();
		
		_server->removeClientFromChannel(this, ch_name);
		if (part_msg.empty())
			part_msg = "\"hasta la vista Baby\"";
		else
			part_msg = "\"" + part_msg + "\"";
		msg.append(cmd + " " + ch_name + " :" + part_msg + END_CHARACTERS);
		sendMsg(msg);
	}
}

void			Client::quit(Message *m){

	std::cout << FC(GREEN ,">\tquit function executed ") << "by client id: " << _id << "\t\t<" << std::endl;
	std::string part_msg = "";

	if (part_msg.empty())
		part_msg = "\"hasta la vista Baby\"";
	else
		part_msg = "\"" + m->params[0] + "\"";
	std::string msg = formatMsgsUsers();
	msg.append("QUIT :Quit: " + part_msg + END_CHARACTERS);
	sendMsg(msg);
	leaveAll("QUIT", part_msg);
	_server->removeClient(this);
	// if (m->params[0].size() == 0)
	// 	_server->removeClientFromServer(this, "");
	// else
	// 	_server->removeClientFromServer(this, m->params[0]);
}

