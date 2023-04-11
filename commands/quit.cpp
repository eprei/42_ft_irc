#include "../srcs/Includes.hpp"

// made by: epresa-c
// modified by :mpons
// TO DO: send messages to the corresponding channel after sendMsgToChannel() function is implemented
void	Client::leaveAll(std::string cmd, std::string part_msg)
{
	std::string msg = formatMsgsUsers();
	if (part_msg.empty())
		part_msg = "hasta la vista Baby";
		
	std::vector<Channel *>::iterator it = _joinedChannels.begin();
	while (it != _joinedChannels.end())
	{
		// std::cout << FC(GREEN, "Canal QUIT =") << ch_name << std::endl;
		std::string ch_name = (*it)->getName();
		msg.append(cmd + " " + ch_name + " :" + part_msg + END_CHARACTERS);
		// sendMsgChannel(msg, *it);
		++it;
	}
	it = _joinedChannels.begin();
	while (it != _joinedChannels.end())
	{
		std::string ch_name = (*it)->getName();
		std::cout << FC(GREEN, "Canal QUIT =") << ch_name << std::endl;
		_server->removeClientFromChannel(this, ch_name);
		it++;
	}
}

void			Client::quit(Message *m){
	std::cout << FC(GREEN ,">\tquit function executed ") << "by client id: " << _id << "\t\t<" << std::endl;
	std::string part_msg = "";

	if (m->params.empty())
		part_msg = "hasta la vista Baby";
	else
		part_msg = m->params[0];
	std::string msg = formatMsgsUsers();
	msg.append("QUIT :Quit: " + part_msg + END_CHARACTERS);
	sendMsg(msg);
	leaveAll("QUIT", part_msg);
	_server->removeClientFromServer(this, "QUIT ");
}

//  [ client : 9000 ] QUIT :me fui 
//  [ server : 6667 ] :pepinsa!~raul@freenode-7kj.edl.vrebei.IP QUIT :Quit: me fui 
//  [ server : 6667 ] ERROR :Closing link: (~raul@xcpe-62-167-164-111.cgn.res.adslplus.ch) [Quit: me fui] 

// 3.1.7 Quit

//       Command: QUIT
//    Parameters: [ <Quit Message> ]

//    A client session is terminated with a quit message.  The server
//    acknowledges this by sending an ERROR message to the client.

//    Numeric Replies:

//            None.

//    Example:

//    QUIT :Gone to have lunch        ; Preferred message format.

//    :syrk!kalt@millennium.stealth.net QUIT :Gone to have lunch ; User
//                                    syrk has quit IRC to have lunch.
